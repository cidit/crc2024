// Board: ESP32 Wrover Kit (all versions)
// Description: Waits for a PS4 controler to connect (PS4.begin()) with the right bt MAC address (c8:c9:a3:d3:32:62) and then sends the data to the UNO by serial
// If running out of memory go to Tools -> Partition scheme : "Huge APP (3MB No OTA/1 MB Spiffs)"
#include <esp_now.h>
#include <WiFi.h>
#include <PS4Controller.h>  // by Juan Pablo Marquez


#define BAUD_RATE 115200
#define RXD2 33
#define TXD2 4
#define Debug Serial
#define Uno Serial2

uint8_t broadcastAddress[] = { 0x24, 0x0A, 0xC4, 0xF5, 0x32, 0x50 };
esp_now_peer_info_t peerInfo;
const uint16_t wifiDelay = 50, ps4Delay = 50;
unsigned long wifiTimer = 0, ps4Timer = 0;
bool ps4Data = false;

#define GYRO_SIZE 12
typedef union {
  struct {
    float yaw;                // 4 bytes
    float pitch;              // 4 bytes
    float roll;               // 4 bytes
  } __attribute__((packed));  // Total : 12 bytes
  uint8_t byteArray[GYRO_SIZE];
} gyroUnion;
gyroUnion gyroData;

#define PS4_SIZE 6
typedef union {
  struct {
    int8_t lStickX;           // 1 byte
    int8_t lStickY;           // 1 byte
    int8_t rStickX;           // 1 byte
    int8_t rStickY;           // 1 byte
    uint8_t L2;               // 1 byte
    uint8_t R2;               // 1 byte
  } __attribute__((packed));  // Total : 6 bytes
  uint8_t byteArray[PS4_SIZE];
} dataStruct;
dataStruct ps4commands;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Debug.print(F("\r\nLast Packet Send Status:\t"));
  status = ESP_NOW_SEND_SUCCESS;
  if (status == 0) {
    Debug.println(F("Delivery Success"));
  } else {
    Debug.println(F("Delivery Fail"));
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
 
}

void onConnect() {
  Debug.println(F("Connected!"));
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
  Debug.println(F("Disconnected!"));
}



void setup() {
  Debug.begin(BAUD_RATE);
  Uno.begin(BAUD_RATE, SERIAL_8N1, RXD2, TXD2);

  PS4.attach(notify);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();

  WiFi.mode(WIFI_STA);
  // Un-comment to see this device's MAC address
  //Debug.println(WiFi.macAddress());
  if (esp_now_init() != ESP_OK) {
    Debug.println(F("Error initializing ESP-NOW"));
    return;
  }
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Debug.println(F("Failed to add peer"));
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

  if (millis() - ps4Timer >= ps4Delay) {
    ps4Timer = millis();
    if (ps4Data) {
      ps4Data = false;
      Uno.write(ps4commands.byteArray, PS4_SIZE);
    }
  }

  if (Uno.available()) {
    Uno.readBytes(gyroData.byteArray, GYRO_SIZE);
  }

  if (millis() - wifiTimer >= wifiDelay) {
    wifiTimer = millis();
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&gyroData.byteArray, sizeof(gyroData.byteArray));

    if (result == ESP_OK) {
      Debug.println(F("Sent with success"));
    } else {
      Debug.println(F("Error sending the data"));
    }
  }
}
