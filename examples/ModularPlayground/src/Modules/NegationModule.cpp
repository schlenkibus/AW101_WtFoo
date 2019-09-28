#include "NegationModule.h"

NegationModule::NegationModule(DSPHost *parent) : DSPModule(parent)
{
  m_input = createInput("IN");
  m_output = createOutput("OUT");
}

void NegationModule::tick() {
  DSPContainer::tick();
  m_output->set(std::abs(m_input->getSignal()) - 1.0f);
}
