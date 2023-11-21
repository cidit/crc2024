// Board: ESP32 Wrover Kit (all versions)
// Description: Waits for a PS4 controler to connect (PS4.begin()) with the right bt MAC address (c8:c9:a3:d3:32:62) and then sends the data to the UNO by serial

#include <PS4Controller.h> // by Juan Pablo Marquez

#define BAUD_RATE 9600
#define RXD2 33
#define TXD2 4

#define TRANSFER_SIZE 6
const uint8_t serialDelay = 100; // Delay in ms between each serial instruction packet sent

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

unsigned long serialTimer = 0;
bool ps4Data = false;


void onConnect() {
  Serial.println("Connected!");
}

void notify() {
  ps4Data = true;
  ps4commands.lStickX = PS4.LStickX();
  ps4commands.lStickY = PS4.LStickY();
  ps4commands.rStickX = PS4.RStickX();
  ps4commands.rStickY = PS4.RStickY();
  ps4commands.L2 = PS4.L2Value();
  ps4commands.R2 = PS4.R2Value();
}

void onDisConnect() {
  Serial.println("Disconnected!");
}

void setup() {
  Serial.begin(BAUD_RATE);
  Serial2.begin(BAUD_RATE, SERIAL_8N1, RXD2, TXD2);
  PS4.attach(notify);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready!");
}

void loop() {
  if (ps4Data) {
    if (millis() - serialTimer > serialDelay) {
      ps4Data = false;
      serialTimer = millis();
      Serial2.write(ps4commands.byteArray, TRANSFER_SIZE);
    }
  }
}
