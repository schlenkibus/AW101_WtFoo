#pragma once
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ESP8266WiFiMulti.h>

class HomeLine
{
 private:
  String m_hello;
  bool m_connected = false;

 public:
  template <typename tHelloCB>
  HomeLine(const tHelloCB& cb)
      : m_hello {}
  {
    webSocketClient.begin("101.101.101.101", 18700, "/welcome/");
    webSocketClient.onEvent([this] (WStype_t type, uint8_t* payload, size_t length) { webSocketEvent(type, payload, length); });
    //webSocketClient.setReconnectInterval(5000);

    m_hello = cb();
  }

  bool isConnected() {
    return m_connected;
  }

  void webSocketEvent(WStype_t type, uint8_t* payload, size_t length)
  {
    switch(type)
    {
      case WStype_DISCONNECTED:
        Serial.printf("Disconnected!\n");
        m_connected = false;
        break;
      case WStype_CONNECTED:
      {
        Serial.printf("Connected to url: %s\n", payload);
        webSocketClient.sendTXT(m_hello);
        m_connected = true;
        Serial.println(m_hello);
      }
      break;
      case WStype_TEXT:
        Serial.printf("Got text: %s\n", payload);
        webSocketClient.sendTXT("PONG");
        break;
    }
  }

  template <typename T> void sendMessage(T message)
  {
    webSocketClient.sendTXT(message);
    Serial.print("Send: ");
    Serial.println(message);
  }

  void loop()
  {
    webSocketClient.loop();
  }

 private:
  WebSocketsClient webSocketClient;
};