#pragma once
#include "ModuleWidget.h"
#include <examples/ModularPlayground/src/Modules/MagicNumberModule.h>
#include <examples/ModularPlayground/src/WebUI/GenericWidgets/ParameterSlider.h>

template <size_t size> class MagicNumberModuleWidget : public ModuleWidget {
public:
  MagicNumberModuleWidget(MagicNumberModule<size> *module)
      : ModuleWidget(module), m_numberModule{module} {
  }

protected:
  MagicNumberModule<size> *m_numberModule;
};
