#pragma once
#include <libDSP/include/Modules/DSPModule.h>

template <size_t size> class MagicNumberModule : public DSPModule {
public:
  const char *TYPE() const override { return "MagicNumberModule"; }
  explicit MagicNumberModule(DSPHost *host) : DSPModule(host) {
    for (auto i = 0; i < size; i++) {
      createParameter("NUMBER " + std::to_string(i), 0.0, 0.0, 1.0);
      createOutput("OUT " + std::to_string(i));
    }

    int i = 0;
    for (auto o : getOutputs()) {
      m_numbers[i++] = o;
    }

    i = 0;
    for (auto o : getParameters()) {
        m_NumberParameters[i++] = o;
    }
  }

  void tick() override {
    DSPContainer::tick();

    for (auto i = 0; i < size; i++) {
      m_numbers[i]->set(m_NumberParameters[i]->getValue());
    }
  }

protected:
  std::array<Output *, size> m_numbers;
  std::array<Parameter *, size> m_NumberParameters;
};
