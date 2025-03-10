#ifndef ESPNOWHANDLER_H
#define ESPNOWHANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

class ESPNowHandler {
   public:
    ESPNowHandler(const uint8_t *peerMacAddress, bool useLR = false, bool printDebug = false);
    bool init();
    bool send_data(const String &data);
    void on_data_sent(const uint8_t *mac_addr, esp_now_send_status_t status);
    void on_data_recv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int data_len);
    String get_data();

   private:
    uint8_t peerMacAddress[6];
    static void on_data_sent_static(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void on_data_recv_static(const esp_now_recv_info_t *recv_info, const uint8_t *data,
      int data_len);
    static ESPNowHandler *instance;

    String m_data;
    bool m_useLR;
    bool m_printDebug;
};

#endif  // ESPNOWHANDLER_H