//How to manipulate digitalOutputs
//https://robocrc.atlassian.net/wiki/spaces/AR/pages/554270747/SetDigitalOutput

//How to access the state of the controller buttons
//https://robocrc.atlassian.net/wiki/spaces/AR/pages/560464350/CrcLib+How+to+access+the+remote+controller+buttons
#include <CrcLib.h>
#include <Encoder.h>

int joystickLeftX;
int joystickLeftY;
int joystickRightX;
int joystickRightY; 

bool boutonB = false; 
bool boutonL1 = false; 
bool boutonX = false;

volatile int encoder = 0;


// Encoder myEnc(CRC_DIG_2 , CRC_DIG_4 );
Encoder myEnc(2,3);

// void count() {
//   encoder += 1;
//   Serial.println(encoder);
// }


void initialistaionCrc(){

  CrcLib::Initialize();
  // CrcLib::SetDigitalPinMode(CRC_DIG_1, INPUT);
  CrcLib::InitializePwmOutput(CRC_PWM_1);
  CrcLib::InitializePwmOutput(CRC_PWM_2);



}
void lectureManette() {


  joystickLeftY  = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y);
  joystickLeftX  = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y);
  

  joystickRightY = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_Y);
  joystickRightX = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_Y);

  boutonB = CrcLib::ReadDigitalChannel(BUTTON::COLORS_RIGHT);
  boutonX = CrcLib::ReadDigitalChannel(BUTTON::COLORS_DOWN);
  boutonL1= CrcLib::ReadDigitalChannel(BUTTON::R1);

}


void bougerRobot() {

  CrcLib::MoveTank(joystickLeftY, joystickRightY, CRC_PWM_1, CRC_PWM_2);  //Front~Back

  CrcLib::MoveTank(joystickLeftX, joystickRightX, CRC_PWM_2, CRC_PWM_1);  //Left~Right

}

// void lift() {

//   if (bouton){

//     if(/*encodeur*/ <= /*valeur*/){ //direction needed

//       CrcLib::SetPwmOutput(CRC_PWM_3,127);

//     }else {
//       CrcLib::SetPwmOutput(CRC_PWM_3,1);
//     }


//   }else {
    
//     CrcLib::SetPwmOutput(CRC_PWM_3,0);
//     valuerEnco = 0 ; 
//   }

// }

// void lanceur(){

//   if (butonX){

//     CrcLib::SetPwmOutput(CRC_PWM_3,127); // wait 500ms before stop?
//     //2 motors ? 

//   }

// }

void kriby(){


}

void setup() {

  Serial.begin(9600);

  initialistaionCrc();
  

  //Set up DIO Port 1 as an Output
  
  //CrcLib::SetDigitalPinMode(CRC_ENCO_A, INPUT);
  
  //CrcLib::SetDigitalPinMode(CRC_ENCO_B,INPUT);
  //pinMode(3, INPUT);
  //attachInterrupt(digitalPinToInterrupt(CRC_ENCO_A), count, CHANGE);


  /* 
    The rest of your setup code
    ...
     */
}
long position = -999;

void loop() {


  CrcLib::Update();

  

  lectureManette();

  bougerRobot();
  //Serial.println(myEnc.read));
  //Serial.println(encoder);
  // int ChA = CrcLib::GetDigitalInput(CRC_DIG_1);
  // Serial.println(ChA);
  // int ChB = CrcLib::GetDigitalInput(CRC_DIG_2);
  // Serial.println(ChB);
  //Check Green Triangle button state (on a ps3 controller)
  // if (CrcLib::ReadDigitalChannel(BUTTON::COLORS_UP) == HIGH)  //Button is pressed
  // {
  //   CrcLib::SetDigitalOutput(CRC_DIG_1, LOW);  //Output 0V on pin
  //   CrcLib::SetPwmOutput(CRC_PWM_1, 127);
  // }


  //Button is not pressed
  //Serial.println("JOYSTICK1_Y : "+String(joyL));
  //CrcLib::SetDigitalOutput(CRC_DIG_1, HIGH);              //Output 5V on pin


  //Button is not pressed
  // int lol = CrcLib::GetDigitalInput(CRC_ENCO_A);
  // Serial.println(lol);
  volatile long newPos = myEnc.read();
  //Serial.println(newPos);
  // volatile int position = 0;
  // volatile int i;

    if (newPos != position) {
      position = newPos;

      // i++;
      Serial.println(position);
      //Serial.println("lj  I : "+ String(i)  );
    }

  /* 
    The rest of your looping code
    ...
    */
}