#include "ModularWebUI.h"
#include "../ModularPlaygroundApplication.h"

#include "ModuleWidgets/BangButtonModuleWidget.h"
#include "NodeWidgets/DSPInputWidget.h"
#include "PlaygroundToolboxWidget.h"
#include "WireOverlayWidget.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WLabel.h>

#include "ModuleWidgets/ModuleContainer.h"

ModularWebUI::ModularWebUI(const Wt::WEnvironment &env,
                           ModularPlaygroundApplication &app,
                           const char *basePath)
    : Wt::WApplication{env}, m_application{app} {
  init();
}

void ModularWebUI::init() {
  Wt::WJavaScriptPreamble pre{m_javascriptScope, Wt::JavaScriptObjectType::JavaScriptFunction, "", ""};

  require("dom_helpers.js");

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

  m_moduleContainer = dynamic_cast<ModuleContainer*>(root()->addWidget(
      std::make_unique<ModuleContainer>(m_application.getModules())));

  m_overlay = m_moduleContainer->addWidget(
      std::make_unique<WireOverlayWidget>(&m_application, this));

  auto redraw = root()->addWidget(std::make_unique<Wt::WPushButton>());
  redraw->clicked().connect(m_overlay, &WireOverlayWidget::requestRedraw);
  redraw->setText("redraw!");

  useStyleSheet("modular.css");
}

float ModularWebUI::getWindowX() const { return root()->width().value(); }

float ModularWebUI::getWindowY() const { return root()->height().value(); }
std::vector<ModuleWidget *> ModularWebUI::getModuleContainer() {
  std::vector<ModuleWidget *> ret{};
  for(auto& widget: m_moduleContainer->children())
    if(auto modWidget = dynamic_cast<ModuleWidget*>(widget))
      ret.emplace_back(modWidget);
  return ret;
}
