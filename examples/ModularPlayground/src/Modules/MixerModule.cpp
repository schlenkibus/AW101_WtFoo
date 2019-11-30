#include "MixerModule.h"

MixerModule::MixerModule(DSPHost *parent)
    : DSPModule(parent)
{

  for(auto i = 0; i < 2; i++)
    createInput("IN" + std::to_string(i));

  m_out = createOutput("OUT");
}

void MixerModule::tickInternals()
{
  auto temp = 0.0;

  for(auto i : m_inputs)
  {
    temp += i->getSignal();
  }

  m_out->setSignal(temp / 2.0);
}
