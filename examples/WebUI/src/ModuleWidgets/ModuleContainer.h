#pragma once
#include <Wt/WContainerWidget.h>
#include <libDSP/include/Modules/DSPModule.h>
#include <NodeWidgets/DSPOutputWidget.h>
#include <NodeWidgets/DSPInputWidget.h>

class ModularWebUI;

class ModuleContainer : public Wt::WContainerWidget
{
 public:
  explicit ModuleContainer(const std::vector<DSPModule*>& modules, ModularWebUI* parent);
  void instantiate(DSPModule* module);

  DSPOutputWidget* findWidget(const DSPOutputNode* o) const;
  DSPInputWidget* findWidget(const DSPInputNode* o) const;

 private:
  ModularWebUI* m_parent;
};
