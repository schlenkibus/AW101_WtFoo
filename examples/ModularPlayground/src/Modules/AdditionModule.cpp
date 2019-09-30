#include "AdditionModule.h"

AdditionModule::AdditionModule(DSPHost *host) : DSPModule(host) {
  createInput("1");
  createInput("2");

  m_out = createOutput("SUM");
  m_inI = findInput("1");
  m_inII = findInput("2");
}

void AdditionModule::tick() {
  DSPContainer::tick();
  m_out->set(m_inI->getSignal() + m_inII->getSignal());
}

const char *AdditionModule::getName() { return "Addition Module"; }
