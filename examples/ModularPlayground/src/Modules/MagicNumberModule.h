#pragma once
#include <libDSP/include/Modules/DSPModule.h>

template<size_t size>
class MagicNumberModule : public DSPModule {
public:
  const char *TYPE() const override { return "MagicNumberModule"; }
  explicit MagicNumberModule(DSPHost* host) : DSPModule(host) {
        for(auto i = 0; i < size; i++) {
            createOutput("OUT" + std::to_string(i));
        }

        int i = 0;
        for(auto o: getOutputs()) {
            m_numbers[i++] = o;
        }
    }

    void setSignal(size_t number, float value) {
        if(number < size) {
            m_numbers[number]->set(value);
        }
    }

  protected:
    std::array<Output*, size> m_numbers;
};

