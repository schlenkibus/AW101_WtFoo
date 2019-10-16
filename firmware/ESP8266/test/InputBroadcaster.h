#pragma once
#include <WebSocketsServer.h>

class InputBroadcaster
{
 public:
  InputBroadcaster(int port)
      : m_server { port, "/inputs/" }
  {
    m_server.onEvent([this] (unsigned char num, WStype_t type, uint8_t* payload, size_t length) { webSocketEvent(num, type, payload, length); });
    m_server.begin();
  }

  void webSocketEvent(unsigned char num, WStype_t type, uint8_t* payload, size_t length)
  {
    switch(type)
    {
      case WStype_DISCONNECTED:
        Serial.printf("Disconnected!\n");
        break;
      case WStype_CONNECTED:
      {
        Serial.printf("Connected to url: %s\n", payload);
      }
        break;
      case WStype_TEXT:
        Serial.printf("Got text: %s\n", payload);
        break;
    }
  }

  void sendMessage(String& s)
  {
    m_server.broadcastTXT(s);
    Serial.println(s);
  }

  void loop()
  {
    m_server.loop();
  }

 private:
  WebSocketsServer m_server;
};
