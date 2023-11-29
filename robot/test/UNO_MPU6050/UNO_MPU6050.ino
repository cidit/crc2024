
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

//MPU6050 accelgyro;
MPU6050 mpu;

#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
const double g = 9.81;
// MPU control/status vars
bool dmpReady = false;   // set true if DMP init was successful
uint8_t mpuIntStatus;    // holds actual interrupt status byte from MPU
uint8_t devStatus;       // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;     // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;      // count of all bytes currently in FIFO
uint8_t fifoBuffer[64];  // FIFO storage buffer

// orientation/motion vars
Quaternion q;         // [w, x, y, z]         quaternion container
VectorInt16 aa;       // [x, y, z]            accel sensor measurements
VectorInt16 gy;       // [x, y, z]            gyro sensor measurements
VectorInt16 aaReal;   // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;  // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;  // [x, y, z]            gravity vector
float euler[3];       // [psi, theta, phi]    Euler angle container
float ypr[3];         // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// Alpha factor, to smooth out accelerometer readings
float alpha = 0.04;
// Timers
unsigned long spdTimer = 0, posTimer = 0;
uint8_t serialDelay = 1;
// Volatile global to use in the interrupt function, indicates whether MPU interrupt pin has gone high
volatile bool mpuInterrupt = false;

// Interrupt routine, keep as short as possible
void dmpDataReady() {
  mpuInterrupt = true;
}

// Funtion used to smooth out readings
// Takes signed 16bit numbers in and returns the sum of a percentage of the last value plus the remainder of the new one
int16_t numFiltering(int16_t newVal, int16_t lastVal) {
  return (1 - alpha) * lastVal + alpha * newVal;
}

double calculateAccel(int16_t accel) {
  if (abs(accel) > 20) {
    return accel / 16384.0F * g * 100.0F;
  } else {
    return 0.0F;
  }
}
// Calculates the new speed (in m/s) for a given acceleration and time value, returns the new speed in m/s
double calculateSpeed(double lastSpeed, double accel) {
  double retVal = lastSpeed;
  unsigned long deltaT = micros() - spdTimer;
  // Ignore small changes
  if (abs(accel) > 0.01) {
    // New speed equals to the last speed + the speed variation (accel * time), accel divided by 1000 to get output in m/s
    retVal += accel * deltaT / 1000000.0F ;
  }
  // Return the value, modified or not
  return retVal;
}

// Calculates the new position (in meters) for a given speed and time value, return the position in meters
double calculatePos(double lastPos, double speed) {
  double retVal = lastPos;
  unsigned long deltaT = micros() - posTimer;
  // New position equals to the last position + the position variation (speed * time)
  if (abs(speed) > 0.01) {
    retVal += speed * deltaT / 1000000.0F;
  }
  // Return the value, modified or not
  return retVal;
}

void setup() {

  Wire.begin();
  Wire.setClock(400000);  // 400kHz I2C clock. Comment this line if having compilation difficulties
  Serial.begin(115200);
  delay(1000);

  // initialize device
  Serial.println("Initializing I2C devices...");
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();


  // supply your own gyro offsets here, scaled for min sensitivity
  
  // Display offsets
  /*
  mpu.setXAccelOffset(-556);
  mpu.setYAccelOffset(-797);
  mpu.setZAccelOffset(1201);
  mpu.setXGyroOffset(106);
  mpu.setYGyroOffset(33);
  mpu.setZGyroOffset(-36);
  */
  

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // Calibration Time: generate offsets and calibrate our MPU6050
    mpu.CalibrateAccel(18);
    mpu.CalibrateGyro(618);
    Serial.println();
    mpu.PrintActiveOffsets();
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
    Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
    Serial.println(F(")..."));
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
  // Git rid of first Fifo packets...
  unsigned long stabilizeTimer = millis() + 1000;
  while (millis() < stabilizeTimer) {
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetAccel(&aa, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
      mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
    }
  }
  // Start timers
  spdTimer = posTimer = micros();
}

void loop() {
  // Static variables used for calculations
  static int16_t gX = 0, gY = 0, gZ = 0;
  static double accX = 0, accY = 0, accZ = 0;
  static double spdX = 0, spdY = 0, spdZ = 0;
  static double posX = 0, posY = 0, posZ = 0;

  // if programming failed, don't try to do anything
  if (!dmpReady) return;
  // read a packet from FIFO
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {  // Get the Latest packet
    // Get DMP info, raw values are in mm/s2 for acceleration, yaw/ptch/roll is in degrees (from initial position)
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetAccel(&aa, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
    mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
    // Eleminate noise on accelerometer
    gX = numFiltering(aaWorld.x, gX);
    gY = numFiltering(aaWorld.y, gY);
    gZ = numFiltering(aaWorld.z + 10, gZ);

    // Calculate acceleration in gs
    accX = calculateAccel(gX);
    accY = calculateAccel(gY);
    accZ = calculateAccel(gZ);

    // Calculte the new instantaneous speeds
    spdX = calculateSpeed(spdX, accX);
    spdY = calculateSpeed(spdY, accY);
    spdZ = calculateSpeed(spdZ, accZ);
    spdTimer = micros();
    // Calculate the new position
    posX = calculatePos(posX, spdX);
    posY = calculatePos(posY, spdY);
    posZ = calculatePos(posZ, spdZ);
    posTimer = micros();

    // Print info on serial monitor every X milliseconds
    //if (millis() >= serialTimer) { serialTimer += serialDelay; }

    // Display Yaw/pitch/roll
    Serial.print("gyro(deg)\t");
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[2] * 180 / M_PI);
    // Display accelerometer info, in mm/s2
    Serial.print("\t| a\t");
    Serial.print(accX);
    Serial.print("\t");
    Serial.print(accY);
    Serial.print("\t");
    Serial.print(accZ);
    // Display speed in m/s
    Serial.print("\t| s\t");
    Serial.print(spdX);
    Serial.print("\t");
    Serial.print(spdY);
    Serial.print("\t");
    Serial.print(spdZ);
    // Display position in meters
    Serial.print("\t| p\t");
    Serial.print(posX);
    Serial.print("\t");
    Serial.print(posY);
    Serial.print("\t");
    Serial.print(posZ);
    Serial.println();
  }
}
