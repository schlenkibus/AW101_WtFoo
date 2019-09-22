#include "ModularWebUI.h"
#include "../ModularPlaygroundApplication.h"
#include "../Modules/BangModule.h"
#include "../Modules/DrumModule.h"
#include "../Modules/DuplicationModule.h"
#include "../Modules/MixerModule.h"
#include "../Modules/MultiplyModule.h"
#include "ModuleWidgets/MagicNumberModuleWidget.h"

#include "ModuleWidgets/BangButtonModuleWidget.h"
#include "ModuleWidgets/DrumModuleWidget.h"
#include "NodeWidgets/DSPInputWidget.h"
#include "PlaygroundToolboxWidget.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <examples/ModularPlayground/src/Modules/MagicNumberModule.h>
#include <examples/ModularPlayground/src/Modules/SineOscillatorModule.h>
#include <examples/ModularPlayground/src/WebUI/ModuleWidgets/SineOscillatorModuleWidget.h>

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
      std::make_unique<DSPInputWidget>(m_application.getLeftChannel()));
  root()->addWidget(
      std::make_unique<DSPInputWidget>(m_application.getRightChannel()));

  for (auto &module : m_application.getModules()) {
    auto type = module->TYPE();
    if (strcmp(type, "BangModule") == 0) {
      root()->addWidget(std::make_unique<BangButtonModuleWidget>(
          dynamic_cast<BangModule *>(module.get())));
    } else if (strcmp(type, "DrumModule") == 0) {
        root()->addWidget(std::make_unique<DrumModuleWidget>(
                dynamic_cast<DrumModule *>(module.get())));
    } else if (strcmp(type, "SineOscillatorModule") == 0) {
      root()->addWidget(std::make_unique<SineOscillatorModuleWidget>(
          dynamic_cast<SineOscillatorModule *>(module.get())));
    }  else if (strcmp(type, "MagicNumberModule") == 0) {
      auto mod = dynamic_cast<MagicNumberModule<5>*>(module.get());
      root()->addWidget(std::make_unique<MagicNumberModuleWidget<5>>(mod));
    } else {
      root()->addWidget(std::make_unique<ModuleWidget>(module.get()));
    }
  }

  // root()->addWidget(std::make_unique<WireOverlayWidget>(m_application));
  useStyleSheet("modular.css");
}

void ModularWebUI::createModuleFromString(ModularPlaygroundApplication *app,
                                          const char *name) {
  if (strcmp(name, "BangModule") == 0) {
    app->createModule<BangModule>(app);
  } else if (strcmp(name, "DrumModule") == 0) {
    app->createModule<DrumModule>(app);
  } else if (strcmp(name, "MultiplyModule") == 0) {
    app->createModule<MultiplyModule>(app);
  } else if (strcmp(name, "DuplicationModule") == 0) {
    app->createModule<DuplicationModule>(app);
  } else if (strcmp(name, "MixerModule") == 0) {
    app->createModule<MixerModule>(app);
  } else if (strcmp(name, "SineOscillatorModule") == 0) {
      app->createModule<SineOscillatorModule>(app);
  } else if (strcmp(name, "MagicNumberModule") == 0) {
      app->createModule<MagicNumberModule<5>>(app);
  }
}
