#include "DSPClock.h"

void DSPClock::tick() {
  if(m_inputRunning)
    if(m_inputRunning->signal == 0)
      return;

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
  m_inputRunning = dynamic_cast<DSPInput*>(createNode<DSPInput>());
}

void DSPClock::print(std::ostream &stream) const {
    DSPContainer::print(stream);
    stream << "CYCLE TIME: " << m_targetTick << "\n";
}

void DSPClock::removeNode(const LibUUID::UUID &uuid) {
  if(uuid != m_inputRunning->m_uuid)
    DSPContainer::removeNode(uuid);
  else
    std::cerr << "can not remove internal signal!";
}

DSPInput* DSPClock::getInputNode(){
    return m_inputRunning;
}
