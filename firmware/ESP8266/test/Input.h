#pragma once
#include "InputBroadcaster.h"

class Input
{
public:
    Input(const int pin, const int id, InputBroadcaster* broadcaster)
            : m_pin(pin)
            , m_id(id)
            , m_broadcaster(broadcaster)
    {
        pinMode(pin, INPUT);
    }

    int read() {
        return analogRead(m_pin);
    }

    void loop()
    {
        auto value = read();
        if(m_lastValue - value > 4 || m_lastValue - value < -4)
        {
            String s(value);
            m_broadcaster->sendMessage(String(m_id) + String(" ") + s);
            m_lastValue = value;
        }
    }

private:
    InputBroadcaster* m_broadcaster;
    int m_lastValue {};
    const int m_id;
    const int m_pin;
};
