#include "SineOscillatorModuleWidget.h"
#include <examples/ModularPlayground/src/WebUI/GenericWidgets/ParameterSlider.h>

SineOscillatorModuleWidget::SineOscillatorModuleWidget(
    SineOscillatorModule *module)
    : ModuleWidget(module), m_osc(module) {
}
