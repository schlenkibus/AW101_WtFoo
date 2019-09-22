#pragma once
#include "../NodeWidgets/DSPInputWidget.h"
#include "../NodeWidgets/DSPOutputWidget.h"
#include <Wt/WContainerWidget.h>
#include <examples/ModularPlayground/src/WebUI/GenericWidgets/ParameterSlider.h>
#include <libDSP/include/Modules/DSPModule.h>

class ModuleWidget : public Wt::WContainerWidget {
public:
  ModuleWidget(DSPModule *module);

protected:
  DSPModule *m_module;
  std::vector<DSPInputWidget *> m_inputs;
  std::vector<DSPOutputWidget *> m_outputs;
  std::vector<ParameterSlider *> m_parameters;
};
