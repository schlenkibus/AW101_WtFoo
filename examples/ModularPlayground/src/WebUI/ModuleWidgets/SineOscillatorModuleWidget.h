#pragma once
#include "ModuleWidget.h"
#include <examples/ModularPlayground/src/Modules/SineOscillatorModule.h>

class SineOscillatorModuleWidget : public ModuleWidget {
public:
  explicit SineOscillatorModuleWidget(SineOscillatorModule *module);

private:
  SineOscillatorModule *m_osc;
};
