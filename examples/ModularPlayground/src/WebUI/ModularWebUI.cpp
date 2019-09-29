#include "ModularWebUI.h"
#include "../ModularPlaygroundApplication.h"

#include "ModuleWidgets/BangButtonModuleWidget.h"
#include "NodeWidgets/DSPInputWidget.h"
#include "PlaygroundToolboxWidget.h"
#include "WireOverlayWidget.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WPushButton.h>

#include "ModuleWidgets/ModuleContainer.h"

ModularWebUI::ModularWebUI(const Wt::WEnvironment &env,
                           ModularPlaygroundApplication &app,
                           const char *basePath)
    : Wt::WApplication{env}, m_application{app} {
  init();
}

void ModularWebUI::init() {
  Wt::WJavaScriptPreamble pre{
      m_javascriptScope, Wt::JavaScriptObjectType::JavaScriptFunction, "", ""};

  require("dom_helpers.js");

  root()->clear();

  m_domProxy = std::make_unique<WidgetDOMSizeProxy>(root());

  auto header = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  header->addWidget(std::make_unique<PlaygroundToolboxWidget>(&m_application));
  header->setStyleClass("header-container");
  header->setStyleClass("style-base");
  auto audioOut = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  audioOut->setStyleClass("output-container");
  audioOut->setStyleClass("style-base");
  audioOut->addWidget(std::make_unique<Wt::WLabel>())->setText("Master Audio");
  audioOut->addWidget(
      std::make_unique<DSPInputWidget>(m_application.getLeftChannel()));
  audioOut->addWidget(
      std::make_unique<DSPInputWidget>(m_application.getRightChannel()));

  root()->setStyleClass("root-container");

  m_moduleContainer = dynamic_cast<ModuleContainer *>(root()->addWidget(
      std::make_unique<ModuleContainer>(m_application.getModules())));

  m_overlay = root()->addWidget(
      std::make_unique<WireOverlayWidget>(&m_application, this));

  auto redraw = root()->addWidget(std::make_unique<Wt::WPushButton>());
  redraw->clicked().connect(m_overlay, &WireOverlayWidget::requestRedraw);
  redraw->setText("redraw!");

  useStyleSheet("modular.css");
}

std::vector<ModuleWidget *> ModularWebUI::getModuleWidgets() {
  std::vector<ModuleWidget *> ret{};
  for (auto &widget : m_moduleContainer->children())
    if (auto modWidget = dynamic_cast<ModuleWidget *>(widget))
      ret.emplace_back(modWidget);
  return ret;
}

const WidgetDOMSizeProxy *ModularWebUI::getDomProxy() const {
  return m_domProxy.get();
}

std::vector<Connection> ModularWebUI::getConnections() {
  std::vector<Connection> ret{};

  auto &modules = m_application.getModules();
  for (auto &module : modules) {
    if (module)
      for (auto &in : module->getInputs()) {
        if (auto src = in->connectedTo()) {
          ret.emplace_back(Connection{src, in});
        }
      }
  }

  return ret;
}

ModuleContainer *ModularWebUI::getModuleContainer() {
  return m_moduleContainer;
}
