#include "ModularWebUI.h"
#include "../ModularPlaygroundApplication.h"
#include "../Modules/BangModule.h"
#include "../Modules/DrumModule.h"
#include "../Modules/DuplicationModule.h"
#include "../Modules/MixerModule.h"
#include "../Modules/MultiplyModule.h"
#include "ModuleWidgets/BangButtonModuleWidget.h"
#include "ModuleWidgets/DrumModuleWidget.h"
#include "NodeWidgets/DSPInputWidget.h"
#include "PlaygroundToolboxWidget.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>

ModularWebUI::ModularWebUI(const Wt::WEnvironment &env,
                           ModularPlaygroundApplication &app,
                           const char *basePath)
    : Wt::WApplication{env}, m_application{app} {
  init();
}

void ModularWebUI::init() {
  root()->clear();

  root()->addWidget(std::make_unique<PlaygroundToolboxWidget>(&m_application));
  root()->addWidget(
      std::make_unique<DSPInputWidget>(&m_application.getAudioOut()));

  for (auto &module : m_application.getModules()) {
    auto type = module->TYPE();
    if (strcmp(type, "BangModule") == 0) {
      root()->addWidget(std::make_unique<BangButtonModuleWidget>(
          dynamic_cast<BangModule *>(module.get())));
    } else if (strcmp(type, "DrumModule") == 0) {
      root()->addWidget(std::make_unique<DrumModuleWidget>(
          dynamic_cast<DrumModule *>(module.get())));
    } else {
      root()->addWidget(std::make_unique<ModuleWidget>(module.get()));
    }
  }
}

void ModularWebUI::createModuleFromString(ModularPlaygroundApplication *app,
                                          const char *name) {
  if (strcmp(name, "BangModule") == 0) {
    app->createModule<BangModule>();
  } else if (strcmp(name, "DrumModule") == 0) {
    app->createModule<DrumModule>();
  } else if (strcmp(name, "MultiplyModule") == 0) {
    app->createModule<MultiplyModule>();
  } else if (strcmp(name, "DuplicationModule") == 0) {
    app->createModule<DuplicationModule>();
  } else if (strcmp(name, "MixerModule") == 0) {
    app->createModule<MixerModule>();
  }
}
