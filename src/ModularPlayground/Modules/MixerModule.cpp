#include "MixerModule.h"

MixerModule::MixerModule() {
  for(auto i = 0; i < 2; i++)
    createInput("IN" + std::to_string(i));

  m_out = createOutput("OUT");
}


void MixerModule::tick() {
  DSPContainer::tick();

  auto temp = 0.0;

  for(auto& i: m_inputs) {
    temp+=i.getSignal();
  }

  m_out->set(temp / 2.0);
}

const char *MixerModule::TYPE() const { return "MixerModule"; }
