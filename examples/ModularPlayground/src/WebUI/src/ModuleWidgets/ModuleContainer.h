#pragma once
#include <Wt/WContainerWidget.h>
#include <libDSP/include/Modules/DSPModule.h>
#include <NodeWidgets/DSPOutputWidget.h>
#include <NodeWidgets/DSPInputWidget.h>

class ModuleContainer : public Wt::WContainerWidget {
public:
  explicit ModuleContainer(const std::list<std::unique_ptr<DSPModule>>& modules);
  void instantiate(DSPModule* module);

  DSPOutputWidget* findWidget(Output* o);
  DSPInputWidget* findWidget(Input* o);
};
