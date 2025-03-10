#include "ESP_now_handler.h"

ESPNowHandler *ESPNowHandler::instance = nullptr;

ESPNowHandler::ESPNowHandler(const uint8_t *peerMacAddress, bool useLR, bool printDebug) {
    memcpy(this->peerMacAddress, peerMacAddress, 6);
    instance = this;
    m_useLR = useLR;
    m_printDebug = printDebug;
}

bool ESPNowHandler::init() {
    WiFi.mode(WIFI_STA);
    if (m_useLR) {
        esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_LR);
    } else {
        esp_wifi_set_protocol(WIFI_IF_STA,
          WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N);
    }
    if (esp_now_init() != ESP_OK) {
        return false;
    }

    esp_now_register_send_cb(on_data_sent_static);
    esp_now_register_recv_cb(on_data_recv_static);

    esp_now_peer_info_t peerInfo;
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, peerMacAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        return false;
    }
    return true;
}

bool ESPNowHandler::send_data(const String &data) {
    esp_err_t result = esp_now_send(peerMacAddress, (uint8_t *)data.c_str(), data.length());
    if (m_printDebug) {
        Serial.print("Sending data: ");
        Serial.println(data);
    }
    if (result != ESP_OK) {
        return false;
    }
    return true;
}

void ESPNowHandler::on_data_sent(const uint8_t *mac_addr, esp_now_send_status_t status) {}

void ESPNowHandler::on_data_recv(const esp_now_recv_info_t *recv_info, const uint8_t *data,
  int data_len) {
    m_data = String((char *)data);
    if (m_printDebug) {
        Serial.print("Received data: ");
        Serial.println(m_data);
    }
}

String ESPNowHandler::get_data() {
    String temp_data = m_data;
    m_data = "";
    return temp_data;
}

void ESPNowHandler::on_data_sent_static(const uint8_t *mac_addr, esp_now_send_status_t status) {
    if (instance) {
        instance->on_data_sent(mac_addr, status);
    }
}

void ESPNowHandler::on_data_recv_static(const esp_now_recv_info_t *recv_info, const uint8_t *data,
  int data_len) {
    if (instance) {
        instance->on_data_recv(recv_info, data, data_len);
    }
}