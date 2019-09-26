#include "NumberModule.h"

NumberModule::NumberModule(DSPHost *host) : DSPModule(host) {
  m_numberIn = createParameter("Number", 0.0, -1.0, 1.0);
  m_numberOut = createOutput("OUT");
}

const char *NumberModule::TYPE() const { return "NumberModule"; }

void NumberModule::tick() {
  DSPContainer::tick();
  m_numberOut->set(m_numberIn->getValue());
}
