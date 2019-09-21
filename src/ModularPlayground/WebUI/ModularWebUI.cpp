#include "ModularWebUI.h"
#include "../../DSPNodes/DSPContainer.h"
#include "../../DSPNodes/DSPNode.h"
#include "../../Modules/BangModule.h"
#include "../ModularPlaygroundApplication.h"
#include "ModuleWidgets/BangButtonModuleWidget.h"
#include "NodeWidgets/DSPInputWidget.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>

ModularWebUI::ModularWebUI(const Wt::WEnvironment &env,
                           ModularPlaygroundApplication &app,
                           const char *basePath)
    : Wt::WApplication{env}, m_application{app} {
  init();
}

void ModularWebUI::init() {

  root()->addWidget(std::make_unique<DSPInputWidget>(m_application.getAudioOut()));

  for(auto& module: m_application.getModules()) {
        auto type = module->TYPE();
        if(strcmp(type, "BangModule") == 0) {
            root()->addWidget(std::make_unique<BangButtonModuleWidget>(dynamic_cast<BangModule*>(module.get())));
        }
    }
}
