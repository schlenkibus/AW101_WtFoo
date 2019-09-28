#pragma once
#include "../NodeWidgets/DSPInputWidget.h"
#include "../NodeWidgets/DSPOutputWidget.h"
#include <Wt/WContainerWidget.h>
#include <examples/ModularPlayground/src/WebUI/GenericWidgets/ParameterSlider.h>
#include <examples/ModularPlayground/src/WebUI/GenericWidgets/WidgetDOMSizeProxy.h>
#include <libDSP/include/Modules/DSPModule.h>

class ModuleWidget : public Wt::WContainerWidget {
public:
  ModuleWidget(DSPModule *module);
  const std::vector<DSPInputWidget *> &getInputs() const;
  const std::vector<DSPOutputWidget *> &getOutputs() const;

  const WidgetDOMSizeProxy& getDomProxy() const;
protected:
  WidgetDOMSizeProxy m_proxy;
  DSPModule *m_module;
  std::vector<DSPInputWidget *> m_inputs;
  std::vector<DSPOutputWidget *> m_outputs;
  std::vector<ParameterSlider *> m_parameters;
};
