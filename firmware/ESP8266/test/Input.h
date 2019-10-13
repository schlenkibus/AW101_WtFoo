#pragma once
#include <WebSocketsServer.h>

template <typename T> class Input
{
public:
    Input(const int pin, const int port)
            : m_port { port }
            , m_pin { pin }
            , m_server { nullptr }
    {
        pinMode(pin, INPUT);
    }

    void init() {
        m_server = new WebSocketsServer(m_port);
        m_server->onEvent([this](uint8_t num, WStype_t type, uint8_t *payload, size_t lenght) {
            this->onEvent(num, type, payload, lenght);
        });
        m_server->begin();
    }

    T read() {
        auto val = analogRead(m_pin);
        return static_cast<T>(val);
    }

    void loop()
    {
        m_server->loop();

        auto value = read();
        if(m_lastValue != value)
        {
            String s(value);
            m_server->broadcastTXT(s);
            m_lastValue = value;
        }
    }

    void onEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t lenght)
    {
        switch(type)
        {
            case WStype_DISCONNECTED:
                Serial.printf("[%u] Disconnected!\n", num);
                break;
            case WStype_CONNECTED:
            {
                IPAddress ip = m_server->remoteIP(num);
                Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
            }
                break;
            case WStype_TEXT:
                Serial.printf("[%u] get Text: %s\n", num, payload);
                break;
        }
    }

    String hello() const
    {
        return String("INPUT{PORT{") + String(m_port) + "}}";
    }

private:
    T m_lastValue {};
    WebSocketsServer* m_server{nullptr};
    const int m_port;
    const int m_pin;
};