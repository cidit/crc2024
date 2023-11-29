#include <esp_now.h>
#include <WiFi.h>

#define BAUD_RATE 115200

bool dataRecv = false;
uint8_t broadcastAddress[] = { 0xC8, 0xC9, 0xA3, 0xD3, 0x32, 0x60 };
esp_now_peer_info_t peerInfo;

float yaw = 0.0, pitch = 0.0, roll = 0.0;
/*typedef struct message_struct {
  float yaw;
  float pitch;
  float roll;
} message_struct;
message_struct recvData;
*/
#define RECV_SIZE 12
typedef union {
  struct {
    float yaw;                // 4 bytes
    float pitch;              // 4 bytes
    float roll;               // 4 bytes
  } __attribute__((packed));  // Total : 12 bytes
  uint8_t byteArray[RECV_SIZE];
} gyro_U;
gyro_U gyroData;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  /*Serial.print("\r\nLast Packet Send Status:\t");
  status = ESP_NOW_SEND_SUCCESS;
  if (status == 0) {
    Serial.println("Delivery Success");
  } else {
    Serial.println("Delivery Fail");
  }*/

  
}

// Callback when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  /*memcpy(&recvData, incomingData, sizeof(recvData));
  yaw = recvData.roll;
  pitch = recvData.yaw;
  roll = recvData.pitch;*/
  memcpy(&gyroData.byteArray, incomingData, RECV_SIZE);
  yaw = gyroData.yaw;
  pitch = gyroData.pitch;
  roll = gyroData.roll;
  dataRecv = true;
}
void setup() {
  Serial.begin(BAUD_RATE);
  delay(1000);
  WiFi.mode(WIFI_STA);
  // Un-comment to see this device's MAC address
  //Serial.println(WiFi.macAddress());
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  if (dataRecv) {
    Serial.printf("Yaw/Pitch/Roll:\t%.1f\t%.1f\t%.1f\n", yaw, pitch, roll);
    dataRecv = false;
  }
  

}
