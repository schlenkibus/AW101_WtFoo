#include "NumberModule.h"

NumberModule::NumberModule(DSPHost *host) : DSPModule(host) {
  m_numberIn = createParameter("Number", 0.0, -2000.0, 2000.0, 5);
  m_numberOut = createOutput("OUT");
}

void NumberModule::tick() {
  DSPContainer::tick();
  m_numberOut->set(m_numberIn->getValue());
}
const char *NumberModule::getName() { return "Number"; }
