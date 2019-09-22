#include "SineOscillatorModuleWidget.h"
#include <examples/ModularPlayground/src/WebUI/GenericWidgets/ParameterSlider.h>

SineOscillatorModuleWidget::SineOscillatorModuleWidget(
    SineOscillatorModule *module)
    : ModuleWidget(module), m_osc(module) {
  addWidget(std::make_unique<ParameterSlider>(
      [this](float value) { m_osc->setFrequencyBase(value); }, "Base Frequency", 20, 20000, 3, 300));
}
