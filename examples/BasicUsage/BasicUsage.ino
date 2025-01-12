#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "ESP_now_handler.h"

// Replace with your peer's MAC address
uint8_t peerMacAddress[] = {0x24, 0x6F, 0x28, 0xA1, 0xB2, 0xC3};

ESPNowHandler espNowHandler(peerMacAddress);

void setup() {
    Serial.begin(115200);
    espNowHandler.init();
}

void loop() {
    // Example data to send
    String dataToSend = "Hello, ESP-NOW!";
    espNowHandler.send_data(dataToSend);
    
    // Wait for a while before sending again
    delay(2000);
    
    // Check for received data
    String receivedData = espNowHandler.get_data();
    if (receivedData.length() > 0) {
        Serial.print("Received Data: ");
        Serial.println(receivedData);
    }
}