#include "ModuleContainer.h"
#include "BangButtonModuleWidget.h"

ModuleContainer::ModuleContainer(const std::vector<DSPModule *> &modules)
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
  addWidget(std::make_unique<ModuleWidget>(module));
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