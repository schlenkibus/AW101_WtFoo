#include "RandomModule.h"
#include <algorithm>
#include <chrono>
#include <random>

RandomModule::RandomModule(DSPHost *parent) : DSPModule(parent) {
  createInput("Scaling");
  m_out = createOutput("Noise");
  m_tick = createInput("Clock In");

  m_range = findInput("Scaling");

  std::default_random_engine dre{static_cast<unsigned long>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count())};
  std::uniform_int_distribution<unsigned int> uid(
      std::numeric_limits<unsigned int>::min(),
      std::numeric_limits<unsigned int>::max());
  std::generate(m_cachedRandomness.begin(), m_cachedRandomness.end(), [&]() {
    return static_cast<float>(uid(dre)) / std::numeric_limits<unsigned int>::max();
  });
}

void RandomModule::tick() {
  DSPContainer::tick();


  if (m_tick->getSignal() > 0.0 && !waitingForDown) {
    if (m_readHead == m_cachedRandomness.size()) {
      m_readHead = 0;
    }

    auto val = m_cachedRandomness[m_readHead++];
    m_out->set(m_range->getSignal() * val);
    waitingForDown = true;
  } else if (m_tick->getSignal() <= 0.0 && waitingForDown) {
    waitingForDown = false;
  }

}
