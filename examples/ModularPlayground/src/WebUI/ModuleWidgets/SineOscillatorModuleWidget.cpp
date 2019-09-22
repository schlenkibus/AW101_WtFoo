#include "SineOscillatorModuleWidget.h"
#include <examples/ModularPlayground/src/WebUI/GenericWidgets/ParameterSlider.h>

SineOscillatorModuleWidget::SineOscillatorModuleWidget(
    SineOscillatorModule *module)
    : ModuleWidget(module), m_osc(module) {
  addWidget(std::make_unique<ParameterSlider>(
      [this](float value) { m_osc->setFrequencyBase(value); }, "Base Frequency", 1, 1800, 2, 300));

  addWidget(std::make_unique<ParameterSlider>(
      [this](float value) { m_osc->setFrequencyRange(value); }, "Frequency Range", 1, 200, 2, 5));
}
