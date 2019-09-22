#include "BangModule.h"
#include <libDSP/include/DSPInfo.h>

BangModule::BangModule(DSPHost *parent) : DSPModule{parent}, m_bangLength{} {
  m_bangSignal = createOutput("BANG");
}

const char *BangModule::TYPE() const { return "BangModule"; }

void BangModule::tick() {
  if (m_bangcountdown) {
    if (!m_bangcountdown->tick_check()) {
      m_bangSignal->set(0.0);
      m_bangcountdown.reset();
    }
  }

  DSPContainer::tick();
}

void BangModule::sendBang() {
  m_bangSignal->set(1.0);
  m_bangcountdown = std::make_unique<Countdown<int>>(m_bangLength * DSPInfo::SampleRate);
}

void BangModule::setBangLength(float lengthInSeconds) { m_bangLength = lengthInSeconds; }

float BangModule::getBangLength() const { return m_bangLength; }

const Output *BangModule::getBangSignal() const { return m_bangSignal; }
