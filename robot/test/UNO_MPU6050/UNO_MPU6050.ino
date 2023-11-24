
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"


MPU6050 accelgyro;

const uint8_t maxAlpha = 100;
const float alpha = 0.01;
const uint8_t serialDelay = 40;
const uint16_t calibDelay = 10000;

int16_t ax, ay, az;
int16_t gx, gy, gz;

unsigned long gyroTimer = 0, serialTimer = 0;

int16_t numFiltering(int16_t lastVal, int16_t newVal) {
  return (1 - alpha) * lastVal + newVal * alpha;
}

float calculateAngle(float lastAngle, int16_t angleVariation, uint8_t deltaT) {
  float LSB = 16384.0;
  float retVal = lastAngle;  

  // Ignore small movements
  if (abs(angleVariation) > 200) { retVal += float(angleVariation / LSB) * float(deltaT / (2*PI)); }
  // Keep the angle between 0 and 360°
  if (retVal >= 360.0) { retVal -= 360.0; } 
  else if ( retVal < 0.0) { retVal += 360.0; }
  return retVal;
}

void setup() {

  Wire.begin();
  Serial.begin(38400);
  delay(1000);

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // Calib gyro offsets
  /*accelgyro.setXGyroOffset(100);
  accelgyro.setYGyroOffset(33);
  accelgyro.setZGyroOffset(28);*/
  Serial.println("Present offset configuration (ax, ay, az / gx, gy, gz): ");
  Serial.print(accelgyro.getXAccelOffset());
  Serial.print("\t");  // -76
  Serial.print(accelgyro.getYAccelOffset());
  Serial.print("\t");  // -2359
  Serial.print(accelgyro.getZAccelOffset());
  Serial.print("\t");  // 1688
  Serial.print(accelgyro.getXGyroOffset());
  Serial.print("\t");  // 0
  Serial.print(accelgyro.getYGyroOffset());
  Serial.print("\t");  // 0
  Serial.print(accelgyro.getZGyroOffset());
  Serial.print("\t");  // 0
  Serial.print("\n");
  
  Serial.println("Now mesuring drift, do not move for 10 seconds...");
  gyroTimer = millis();
  bool calibDone = false;
  accelgyro.setXGyroOffset(0);
  accelgyro.setYGyroOffset(0);
  accelgyro.setZGyroOffset(0);
  while (!calibDone) {
    static int16_t accX = 0, accY = 0, accZ = 0, gyrX = 0, gyrY = 0, gyrZ = 0;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    accX = numFiltering(accX, ax);
    accY = numFiltering(accY, ay);
    accZ = numFiltering(accZ, az);
    gyrX = numFiltering(gyrX, gx);
    gyrY = numFiltering(gyrY, gy);
    gyrZ = numFiltering(gyrZ, gz);
    if (millis() - gyroTimer >= calibDelay) {
      calibDone = true;
      Serial.println("Done. Drift measured on gyroscope: "+ String(gyrX) + ", " + String(gyrY) + ", " + String(gyrZ));
      accelgyro.setXGyroOffset(-gyrX/3);
      accelgyro.setYGyroOffset(-gyrY/3);
      accelgyro.setZGyroOffset(-gyrZ/3);
    }
  }
  Serial.println("Setup done, starting main");
  delay(1000);  
}

void loop() {
  static int16_t accX = 0, accY = 0, accZ = 0, gyrX = 0, gyrY = 0, gyrZ = 0;
  static float pitch = 0.0, yaw = 0.0, roll = 0.0;
  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  // these methods (and a few others) are also available
  //accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);
  accX = numFiltering(accX, ax);
  accY = numFiltering(accY, ay);
  accZ = numFiltering(accZ, az);
  gyrX = numFiltering(gyrX, gx);
  gyrY = numFiltering(gyrY, gy);
  gyrZ = numFiltering(gyrZ, gz);


  if (millis() - serialTimer >= serialDelay) {
    serialTimer = millis();
    yaw = calculateAngle(yaw, gyrZ, serialDelay);
    Serial.print(gyrX);
    Serial.print("\t");
    Serial.print(gyrY);
    Serial.print("\t");
    Serial.print(gyrZ);
    Serial.print("\t");
    Serial.println(yaw);
  }
}
