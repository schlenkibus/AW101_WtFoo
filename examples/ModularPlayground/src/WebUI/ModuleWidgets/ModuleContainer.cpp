#include "ModuleContainer.h"
#include "BangButtonModuleWidget.h"
#include "../../Modules/BangModule.h"

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
        dynamic_cast<BangModule*>(module)));
  } else {
    addWidget(std::make_unique<ModuleWidget>(module));
  }
}
