#include "ModuleContainer.h"
#include "../../Modules/BangModule.h"
#include "BangButtonModuleWidget.h"

ModuleContainer::ModuleContainer(
    const std::vector<std::unique_ptr<DSPModule>> &modules) {
  for (auto &m : modules) {
    instantiate(m.get());
  }
  setStyleClass("module-container");
}

void ModuleContainer::instantiate(DSPModule *module) {
  auto type = std::string(module->TYPE());
  if (type == "BangModule") {
    addWidget(std::make_unique<BangButtonModuleWidget>(
        dynamic_cast<BangModule *>(module)));
  } else {
    addWidget(std::make_unique<ModuleWidget>(module));
  }
}

DSPOutputWidget *ModuleContainer::findWidget(Output *o) {
  for (auto &widget : children()) {
    if (auto modWidget = dynamic_cast<ModuleWidget *>(widget)) {
      auto &outs = modWidget->getOutputs();
      for (auto &w : outs) {
        if (w->getOutput()->getUUID() == o->getUUID())
          return w;
      }
    }
  }
  return nullptr;
}

DSPInputWidget *ModuleContainer::findWidget(Input *i) {
  for (auto &widget : children()) {
    if (auto modWidget = dynamic_cast<ModuleWidget *>(widget)) {
      auto &ins = modWidget->getInputs();
      for (auto &w : ins) {
        if (w->getInput()->getUUID() == i->getUUID())
          return w;
      }
    }
  }
  return nullptr;
}