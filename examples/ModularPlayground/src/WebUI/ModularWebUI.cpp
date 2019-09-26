#include "ModularWebUI.h"
#include "../ModularPlaygroundApplication.h"

#include "ModuleWidgets/BangButtonModuleWidget.h"
#include "NodeWidgets/DSPInputWidget.h"
#include "PlaygroundToolboxWidget.h"
#include "WireOverlayWidget.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <examples/ModularPlayground/src/WebUI/ModuleWidgets/ModuleContainer.h>

ModularWebUI::ModularWebUI(const Wt::WEnvironment &env,
                           ModularPlaygroundApplication &app,
                           const char *basePath)
    : Wt::WApplication{env}, m_application{app} {
  init();
}

void ModularWebUI::init() {
  root()->clear();

  auto header = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  header->addWidget(std::make_unique<PlaygroundToolboxWidget>(&m_application));
  header->setStyleClass("header-container");
  auto audioOut = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  audioOut->setStyleClass("output-container");
  audioOut->addWidget(std::make_unique<Wt::WLabel>())->setText("Master Audio");
  audioOut->addWidget(
      std::make_unique<DSPInputWidget>(m_application.getLeftChannel()));
  audioOut->addWidget(
      std::make_unique<DSPInputWidget>(m_application.getRightChannel()));

  root()->setStyleClass("root-container");

  auto moduleContainer = root()->addWidget(
      std::make_unique<ModuleContainer>(m_application.getModules()));

  moduleContainer->addWidget(
      std::make_unique<WireOverlayWidget>(&m_application, this));
  useStyleSheet("modular.css");
}

float ModularWebUI::getWindowX() const { return root()->width().value(); }

float ModularWebUI::getWindowY() const { return root()->height().value(); }
