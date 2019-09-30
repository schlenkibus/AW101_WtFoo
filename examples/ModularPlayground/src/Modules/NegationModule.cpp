#include "NegationModule.h"

NegationModule::NegationModule(DSPHost *parent) : DSPModule(parent)
{
  m_input = createInput("In");
  m_output = createOutput("-In`");
}

void NegationModule::tick() {
  DSPContainer::tick();
  m_output->set(m_input->getSignal() * -1.0f);
}
const char * NegationModule::getName(){
return "Negation Module";
}
