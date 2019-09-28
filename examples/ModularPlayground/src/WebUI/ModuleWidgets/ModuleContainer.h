#pragma once
#include <Wt/WContainerWidget.h>
#include <examples/ModularPlayground/src/WebUI/NodeWidgets/DSPInputWidget.h>
#include <examples/ModularPlayground/src/WebUI/NodeWidgets/DSPOutputWidget.h>
#include <libDSP/include/Modules/DSPModule.h>

class ModuleContainer : public Wt::WContainerWidget {
public:
  explicit ModuleContainer(const std::vector<std::unique_ptr<DSPModule>>& modules);
  void instantiate(DSPModule* module);

  DSPOutputWidget* findWidget(Output* o);
  DSPInputWidget* findWidget(Input* o);
};
