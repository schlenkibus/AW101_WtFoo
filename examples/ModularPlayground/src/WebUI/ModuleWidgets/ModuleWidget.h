#pragma once
#include "../NodeWidgets/DSPInputWidget.h"
#include "../NodeWidgets/DSPOutputWidget.h"
#include <Wt/WContainerWidget.h>
#include <examples/ModularPlayground/src/WebUI/GenericWidgets/ParameterSlider.h>
#include <libDSP/include/Modules/DSPModule.h>

class ModuleWidget : public Wt::WContainerWidget {
public:
  ModuleWidget(DSPModule *module);
  const std::vector<DSPInputWidget *> &getInputs() const;
  const std::vector<DSPOutputWidget *> &getOutputs() const;

  int x = 0;
  int y = 0;
  int w = 0;
  int h = 0;

protected:
  Wt::JSignal<int, int> _position;
  Wt::JSignal<int, int> _scale;

  DSPModule *m_module;
  std::vector<DSPInputWidget *> m_inputs;
  std::vector<DSPOutputWidget *> m_outputs;
  std::vector<ParameterSlider *> m_parameters;
};
