#include "DuplicationModule.h"



const char *DuplicationModule::TYPE() const { return "DuplicationModule"; }

DuplicationModule::DuplicationModule(DSPHost *parent) : DSPModule(parent) {
  m_input = createInput("IN");
  for(auto i = 0; i < 5; i++) {
    createOutput("OUT" + std::to_string(i));
  }
}

void DuplicationModule::tick() {
  DSPContainer::tick();
  const auto signal = m_input->getSignal();

  for(auto& o: m_outputs) {
    o.set(signal);
  }
}
