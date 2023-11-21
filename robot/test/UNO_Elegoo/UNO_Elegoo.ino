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

#define JOYSTICK_DRIFT 10

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

// Function stolen from Elegoo's code
void moveWheels(boolean direction_A, uint8_t speed_A,  //Group A motor parameters
                boolean direction_B, uint8_t speed_B,  //Group B motor parameters
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
    bool dirA = true, dirB = true, enabMotor = true;
    uint8_t speedA = 0, speedB = 0;
    if (ps4commands.lStickY < 0) {
      dirA = false;
      dirB = false;
    }
    if (abs(ps4commands.lStickY) > JOYSTICK_DRIFT) {
      speedA = speedB = map(abs(ps4commands.lStickY), 11, 127, 0, 255);
    } 
    else {
      enabMotor = false;
    }
    moveWheels(dirA, speedA, dirB, speedB, enabMotor);
  }
}
