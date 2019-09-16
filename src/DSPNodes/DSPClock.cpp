#include "DSPClock.h"

void DSPClock::tick() {
  m_currentTick++;

  if(m_currentTick >= m_targetTick) {
    signal = static_cast<float>(!static_cast<bool>(signal));
    m_currentTick = 0;
  }
}

DSPClock::DSPClock(long tickLenght) {
  m_currentTick = 0;
  m_targetTick = tickLenght;
  signal = static_cast<float>(false);
}
