#pragma once
#include "ModuleWidget.h"
#include <examples/ModularPlayground/src/Modules/MagicNumberModule.h>
#include <examples/ModularPlayground/src/WebUI/GenericWidgets/ParameterSlider.h>

template <size_t size> class MagicNumberModuleWidget : public ModuleWidget {
public:
  MagicNumberModuleWidget(MagicNumberModule<size> *module)
      : ModuleWidget(module), m_numberModule{module} {
    for (auto i = 0; i < size; i++) {
      addWidget(std::make_unique<ParameterSlider>(
          [this, i](float value) {
                if(auto o = m_numberModule->findOutput("OUT"+std::to_string(i)))
                    o->set(value);
          },
          "Value " + std::to_string(i), -1.0, 1.0, 2, 0.0));
    }
  }

protected:
  MagicNumberModule<size> *m_numberModule;
};
