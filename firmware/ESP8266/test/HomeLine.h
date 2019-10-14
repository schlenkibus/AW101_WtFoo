#pragma once
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ESP8266WiFiMulti.h>

class HomeLine;

HomeLine* hl = nullptr;

void WebsocketEvent(WStype_t t, uint8_t* p, size_t l);

class HomeLine {
private:
    String m_hello;
public:
  template<typename tHelloCB>
  HomeLine(const tHelloCB& cb) : m_hello{} {
      WiFi.begin("justus-ihm-sein-laptop", "aaaaaaaa");

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
  
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    webSocketClient.begin("101.101.101.101", 18700, "/welcome/");
    webSocketClient.onEvent(WebsocketEvent);
    webSocketClient.setReconnectInterval(5000);

    hl = this;

    m_hello = cb();
  }

  void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("Disconnected!\n");
      break;
    case WStype_CONNECTED: {
      Serial.printf("Connected to url: %s\n", payload);
      webSocketClient.sendTXT(m_hello);
      Serial.println(m_hello);
    } break;
    case WStype_TEXT:
      Serial.printf("Got text: %s\n", payload);
      break;
    }
  }

  template<typename T>
  void sendMessage(T message) {
    webSocketClient.sendTXT(message);
    Serial.print("Send: ");
    Serial.println(message);
  }

  void loop() {
    webSocketClient.loop();
  }

private:
  ESP8266WiFiMulti wifiMulti;
  WebSocketsClient webSocketClient;
};

void WebsocketEvent(WStype_t t, uint8_t* p, size_t l) {
  if(hl) {
    hl->webSocketEvent(t, p, l);
  }
}
