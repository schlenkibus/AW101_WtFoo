#pragma once
#include "../misc/Countdown.h"
#include "DSPModule.h"

class BangModule : public DSPModule {
public:
  BangModule();
  void sendBang();
  void setBangLength(float lengthInSeconds);
  float getBangLength() const;
  const char *TYPE() const override;
  const Output* getBangSignal() const;

protected:
  void tick() override;

private:
  const Output* m_bangSignal;
  float m_bangLength;
  std::unique_ptr<Countdown<int>> m_bangcountdown;
};
