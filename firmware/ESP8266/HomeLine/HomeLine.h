#pragma once
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

class HomeLine {
public:
  HomeLine() {
    WiFi.begin("justus-tower", "aaaaaaaa");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(++i);
      Serial.print(' ');
    }
    Serial.println(WiFi.localIP());

    webSocketClient.begin("101.101.101.101", 18700, "/test/");
    webSocketClient.onEvent(this, &HomeLine::webSocketEvent);
    webSocketClient.setReconnectInterval(5000);
  }

  void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {

    switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("Disconnected!\n");
      break;
    case WStype_CONNECTED: {
      Serial.printf("Connected to url: %s\n", payload);
      webSocketClient.sendTXT(pHardware->greeting());
      webSocketClient.sendTXT("Connected");
    } break;
    case WStype_TEXT:
      Serial.printf("Got text: %s\n", payload);
      // webSocket.sendTXT("message here");
      break;
    }
  }

private:
  HardwareDescription *pHardware = nullptr;
  WebSocketsClient webSocketClient;
};
