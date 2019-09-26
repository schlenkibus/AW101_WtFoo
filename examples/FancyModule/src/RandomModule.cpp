#include "RandomModule.h"
#include <algorithm>
#include <chrono>
#include <random>

RandomModule::RandomModule(DSPHost *parent) : DSPModule(parent) {
  m_range = createParameter("YEET", 0, 0, 1.0, 5);
  m_out = createOutput("WTF");
  m_tick = createInput("STEP RANDOMNESS");

  std::default_random_engine dre{static_cast<unsigned long>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count())};
  std::uniform_int_distribution<int> uid(-10000, 10000);
  std::generate(m_cachedRandomness.begin(), m_cachedRandomness.end(),
                [&]() { return uid(dre) / 10000.0; });
}

const char *RandomModule::TYPE() const { return "RandomModule"; }

void RandomModule::tick() {
  DSPContainer::tick();

  m_out->set(m_cachedRandomness.at(m_readHead) * m_range->getValue());



  if (!waitingForDown && m_tick->getSignal() != 0.0) {
    waitingForDown = true;
  } else if(waitingForDown && m_tick->getSignal() == 0.0) {
    m_readHead++;
    if (m_readHead == m_cachedRandomness.size())
      m_readHead = 0;
    waitingForDown = false;
  }
}
