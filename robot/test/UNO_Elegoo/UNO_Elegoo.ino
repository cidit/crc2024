// Board: Arduino Uno
// Description : Receives PS4 controller input sent by serial from the ESP32 and moves the wheels accordingly
//               For now the rover moves forward and backward only
#define BAUD_RATE 9600
// Pin numbers
#define PIN_Motor_PWMA 5
#define PIN_Motor_PWMB 6
#define PIN_Motor_BIN_1 8
#define PIN_Motor_AIN_1 7
#define PIN_Motor_STBY 3

// Controler settings
#define JOYSTICK_MAX_VALUE 128
#define JOYSTICK_DEADZONE 10  // Defines the deadzone where the control input gets ignored
#define TRIGGER_DEADZONE 20
#define MOTOR_MIN_VALUE 10
#define MOTOR_MAX_VALUE 180


#define TRANSFER_SIZE 6
typedef union {
  struct {
    int8_t lStickX;           // 1 byte
    int8_t lStickY;           // 1 byte
    int8_t rStickX;           // 1 byte
    int8_t rStickY;           // 1 byte
    uint8_t L2;               // 1 byte
    uint8_t R2;               // 1 byte
  } __attribute__((packed));  // Total : 6 bytes
  uint8_t byteArray[TRANSFER_SIZE];
} dataStruct;
dataStruct ps4commands;

// Function stolen from Elegoo's code, controls the motors
void moveWheels(boolean direction_A, uint8_t speed_A,  //Group A motor parameters (right)
                boolean direction_B, uint8_t speed_B,  //Group B motor parameters (left)
                boolean controlED                      //AB enable setting (true)
                )                                      //Motor control
{

  if (controlED)  //Enable motor control？
  {
    digitalWrite(PIN_Motor_STBY, HIGH);
    {  //A...Right

      switch (direction_A)  //movement direction control
      {
        case 1:
          digitalWrite(PIN_Motor_AIN_1, HIGH);
          analogWrite(PIN_Motor_PWMA, speed_A);
          break;
        case 0:

          digitalWrite(PIN_Motor_AIN_1, LOW);
          analogWrite(PIN_Motor_PWMA, speed_A);
          break;
        case 3:
          analogWrite(PIN_Motor_PWMA, 0);
          digitalWrite(PIN_Motor_STBY, LOW);
          break;
        default:
          analogWrite(PIN_Motor_PWMA, 0);
          digitalWrite(PIN_Motor_STBY, LOW);
          break;
      }
    }

    {  //B...Left
      switch (direction_B) {
        case 1:
          digitalWrite(PIN_Motor_BIN_1, HIGH);

          analogWrite(PIN_Motor_PWMB, speed_B);
          break;
        case 0:
          digitalWrite(PIN_Motor_BIN_1, LOW);
          analogWrite(PIN_Motor_PWMB, speed_B);
          break;
        case 3:
          analogWrite(PIN_Motor_PWMB, 0);
          digitalWrite(PIN_Motor_STBY, LOW);
          break;
        default:
          analogWrite(PIN_Motor_PWMB, 0);
          digitalWrite(PIN_Motor_STBY, LOW);
          break;
      }
    }
  } else {
    digitalWrite(PIN_Motor_STBY, LOW);
    return;
  }
}

// Manage the input on the motors according to the joystick position
void manageInputs(void) {
  bool dirA = true, dirB = true, enabMotor = true;
  uint8_t speedA = 0, speedB = 0;
  // Overide the Joystick inputs if triggers are pressed
  if (ps4commands.L2 > TRIGGER_DEADZONE || ps4commands.R2 > TRIGGER_DEADZONE) {
    // Inverse the wheel directions depending on highest input
    if (ps4commands.L2 > ps4commands.R2) {
      dirB = false;
    } else {
      dirA = false;
    }
    // Rotation speed depends on the difference between the inputs. Divided by 2 to prevent from spinning too fast.
    speedA = speedB = abs(ps4commands.L2 - ps4commands.R2) / 2;
  } else {  // If triggers arent pressed, read joystick
    // First check if the joystick is not in neutral position
    if (abs(ps4commands.lStickY) > JOYSTICK_DEADZONE || abs(ps4commands.lStickX) > JOYSTICK_DEADZONE) {
      // Then check which direction the robot is moving
      if (ps4commands.lStickY < 0) {
        // Reverse engines for negative values
        dirA = false;
        dirB = false;
      }
      // Calculate the lenght of the vector
      uint8_t maxSpeed = sqrt(pow(ps4commands.lStickX, 2) + pow(ps4commands.lStickY, 2));
      // Scale the value to match motor inputs
      maxSpeed = map(maxSpeed, JOYSTICK_DEADZONE, JOYSTICK_MAX_VALUE, MOTOR_MIN_VALUE, MOTOR_MAX_VALUE);
      // Calculate the angle
      double angle = atan(abs(ps4commands.lStickX)/abs(ps4commands.lStickY));
      // If the joystick is tilted left, the left wheels moves slower
      if (ps4commands.lStickX < 0) {
        speedA = maxSpeed;
        speedB = cos(angle) * maxSpeed;
      } else { // If not then the right wheels spins slower
        speedA = cos(angle) * maxSpeed;
        speedB = maxSpeed;
      } 
    } else {  // If the joystick is in neutral position, shutdown the engines
      enabMotor = false;
    }
  }
  // Apply output to motors
  moveWheels(dirA, speedA, dirB, speedB, enabMotor);
}

void setup() {
  Serial.begin(BAUD_RATE);
  delay(1000);
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_BIN_1, OUTPUT);
  pinMode(PIN_Motor_STBY, OUTPUT);
}

void loop() {
  static bool cmdRECV = false;
  if (Serial.available()) {
    cmdRECV = true;
    Serial.readBytes(ps4commands.byteArray, TRANSFER_SIZE);
  }

  if (cmdRECV) {
    cmdRECV = false;
    manageInputs();
  }
}
