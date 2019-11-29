#include "DuplicationModule.h"

DuplicationModule::DuplicationModule(DSPHost *parent) : DSPModule(parent) {
  m_input = createInput("In");
  for (auto i = 0; i < 5; i++) {
    createOutput([](int i) {
      std::string s;
      while (i-- > -1)
        s += "'";
      return "Out" + s;
    }(i));
  }
}

void DuplicationModule::tick() {
  DSPContainer::tick();
  const auto signal = m_input->getSignal();

  for (auto &o : m_outputs) {
    o.set(signal);
  }
}
