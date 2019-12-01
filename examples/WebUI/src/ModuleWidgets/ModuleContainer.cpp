#include <ModularWebUI.h>
#include <libDSP/include/Modules/DSPModule.h>
#include "ModuleContainer.h"
#include "BangButtonModuleWidget.h"

ModuleContainer::ModuleContainer(const std::vector<DSPModule *> &modules, ModularWebUI *parent)
    : m_parent { parent }
{
  for(auto &m : modules)
  {
    if(m)
      instantiate(m);
  }

  setStyleClass("module-container");
}

void ModuleContainer::instantiate(DSPModule *module)
{
  if(auto factory = m_parent->getFactory(module))
  {
    addWidget(factory(module));
  }
}

DSPOutputWidget *ModuleContainer::findWidget(const DSPOutputNode *o) const
{
  for(auto widget : children())
  {
    if(auto modWidget = dynamic_cast<ModuleWidget *>(widget))
    {
      auto &outs = modWidget->getOutputs();
      for(auto &w : outs)
      {
        if(w->getOutput()->getName() == o->getName())
          return w;
      }
    }
  }
  return nullptr;
}

DSPInputWidget *ModuleContainer::findWidget(const DSPInputNode *o) const
{
  for(auto widget : children())
  {
    if(auto modWidget = dynamic_cast<ModuleWidget *>(widget))
    {
      auto &ins = modWidget->getInputs();
      for(auto &w : ins)
      {
        if(w->getInput()->getName() == o->getName())
          return w;
      }
    }
  }
  return nullptr;
}