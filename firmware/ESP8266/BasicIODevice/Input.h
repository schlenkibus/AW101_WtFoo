#pragma once
#include "HomeLine.h"

class Input
{
public:
    Input(const int pin, const int id, HomeLine* hl)
            : m_pin(pin)
            , m_id(id)
            , m_broadcaster(hl)
    {
      pinMode(pin, INPUT);

      auto ip = WiFi.localIP();
      ipString = String(ip[0]) + "." + ip[1] + "." + ip[2] + "." + ip[3];
    }

    int read() {
        return analogRead(m_pin);
    }

    void loop()
    {
      if(m_timeout++ > 200) {
        auto value = read();
        if(m_lastValue - value > 3 || m_lastValue - value < -3)
        {
          String s(value);

          m_broadcaster->sendMessage("IP{"+ ipString + "}ID{" + String(m_id) + String("}VALUE{") + s + "}");
          m_lastValue = value;
          m_timeout = 0;
        }
      }
    }

private:
  String ipString;
  HomeLine* m_broadcaster;
  int m_lastValue {};
  const int m_id;
  const int m_pin;

  long m_timeout = 0;
};
