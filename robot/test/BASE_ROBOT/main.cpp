#include <CrcLib.h>
#include <XBee.h>
#include "CrcRemoteState.h"

// bool btnValue;
// byte joyL = 0;
// uint8_t JOYSTICK1_X;

void setup() {
  CrcLib::Initialize();


  CrcLib::InitializePwmOutput(CRC_PWM_1);
  CrcLib::InitializePwmOutput(CRC_PWM_2);

  Serial.begin(115200);  //Open the serial Monitor at a 2000000 baud rate

  /* 
    The rest of your setup code
    ...
     */
}
void loop() {
  CrcLib::Update();



  //joyL = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_X);

  // y = map(x, 1, 50, 50, 1);
  // map(value, fromLow, fromHigh, toLow, toHigh)
// JOYSTICK1_Y = map(ANALOG::JOYSTICK1_Y,-127,126,-63,63);
// JOYSTICK1_X = map(ANALOG::JOYSTICK1_X,-127,126,-63,63);

  if (!CrcLib::IsCommValid()) {
    CrcLib::MoveTank(0, 0, CRC_PWM_1, CRC_PWM_2);
    //CrcLib::SetPwmOutput(unsigned char pin, char value)

  }else{CrcLib::MoveTank(ANALOG::JOYSTICK1_X, ANALOG::JOYSTICK1_Y, CRC_PWM_1, CRC_PWM_2);}
  //CrcLib::SetPwmOutput(CRC_PWM_1, joyL);
  


  //btnValue = CrcLib::ReadDigitalChannel(BUTTON::COLORS_LEFT);
  // Serial.print(" JOYSTICKLX : " + String(joyL) + "   ");
  // Serial.print("BOUTONX : " + String(btnValue));
  // Serial.println();

  /* 
    The rest of your looping code
    ...
    */
}