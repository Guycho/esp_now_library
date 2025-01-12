# esp_now_library/esp_now_library/README.md

# ESPNowHandler Library

## Overview

The ESPNowHandler library provides an easy-to-use interface for ESP-NOW communication on ESP32 devices. It allows for the initialization of ESP-NOW, sending data to peers, and handling callbacks for sent and received data.

## Features

- Initialize ESP-NOW communication
- Send data to a specified peer
- Receive data from peers with callback handling
- Simple API for integration into projects

## Installation

1. Download the library files.
2. Place the `esp_now_library` folder in your Arduino libraries directory (usually located in `Documents/Arduino/libraries`).
3. Restart the Arduino IDE.

## Usage

### Basic Example

To use the ESPNowHandler library, include the header file in your Arduino sketch and create an instance of the `ESPNowHandler` class with the peer's MAC address.

```cpp
#include <ESP_now_handler.h>

// Replace with your peer's MAC address
uint8_t peerMacAddress[] = {0x24, 0x6F, 0x28, 0xA1, 0xB2, 0xC3};

ESPNowHandler espNowHandler(peerMacAddress);

void setup() {
    Serial.begin(115200);
    espNowHandler.init();
}

void loop() {
    espNowHandler.send_data("Hello, ESP-NOW!");
    delay(2000);
}
```

### API Reference

- `ESPNowHandler(const uint8_t *peerMacAddress)`: Constructor that initializes the handler with the peer's MAC address.
- `void init()`: Initializes the ESP-NOW communication.
- `void send_data(const String &data)`: Sends data to the specified peer.
- `void on_data_sent(const uint8_t *mac_addr, esp_now_send_status_t status)`: Callback for sent data status.
- `void on_data_recv(const uint8_t *mac_addr, const uint8_t *data, int data_len)`: Callback for received data.
- `String get_data()`: Retrieves the last received data.

## License

This library is released under the MIT License. See the LICENSE file for more details.