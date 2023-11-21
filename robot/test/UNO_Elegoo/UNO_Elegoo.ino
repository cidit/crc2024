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
#define JOYSTICK_MAX_VALUE 127
#define JOYSTICK_DEADZONE 9  // Defines the deadzone where the joystick's input gets ignored
#define MOTOR_MIN_VALUE 0
#define MOTOR_MAX_VALUE 255
#define MIN_TURN_RATE 75
#define MAX_TURN_RATE 100

#define TRANSFER_SIZE 4
typedef union {
  struct {
    int8_t lStickX;           // 1 octets
    int8_t lStickY;           // 1 octet
    int8_t rStickX;           // 1 octets
    int8_t rStickY;           // 1 octets
  } __attribute__((packed));  // Total : 4 octets
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
  // First check the Y deadzone
  if (abs(ps4commands.lStickY) < JOYSTICK_DEADZONE) {
    // Then check the X deadzone
    if (abs(ps4commands.lStickX) < JOYSTICK_DEADZONE) {
      // Turn off motors if the joystick is in rest position
      enabMotor = false;
    } else {
      // If joystick is pushed sideways, the wheels go in opposition direction
      if (ps4commands.lStickX < 0) {
        // Joystick is pushed to the left
        dirA = true;
        dirB = false;
      } else {
        // Joystick is pushed to the right
        dirA = false;
        dirB = true;
      }
      speedA = speedB = map(abs(ps4commands.lStickX), JOYSTICK_DEADZONE, JOYSTICK_MAX_VALUE, MOTOR_MIN_VALUE, MOTOR_MAX_VALUE);
    }
  } else {  // Otherwise, the wheels are moving in the same direction
    // Reverse motors if joystick is pushed backwards
    if (ps4commands.lStickY < 0) {
      dirA = false;
      dirB = false;
    }  // IF joystick is pushed vertically
    speedA = speedB = map(abs(ps4commands.lStickY), JOYSTICK_DEADZONE, JOYSTICK_MAX_VALUE, MOTOR_MIN_VALUE, MOTOR_MAX_VALUE);
    // IF joystick is pushed vertically only, leave the wheel speeds untouched
    if (abs(ps4commands.lStickX) > JOYSTICK_DEADZONE) {
      // If not then adjust the speed of one of the wheels
      uint8_t turnRate = map(abs(ps4commands.lStickX), JOYSTICK_DEADZONE, JOYSTICK_MAX_VALUE, MIN_TURN_RATE, MAX_TURN_RATE);
      if (ps4commands.lStickX < 0) {
        speedB *= (MAX_TURN_RATE - turnRate) / MAX_TURN_RATE;
      } else {
        speedA *= (MAX_TURN_RATE - turnRate) / MAX_TURN_RATE;
      }
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
