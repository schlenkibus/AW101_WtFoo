#include <utility>

#include "ModularWebUI.h"

#include "ModuleWidgets/BangButtonModuleWidget.h"
#include "NodeWidgets/DSPInputWidget.h"
#include "PlaygroundToolboxWidget.h"
#include "WireOverlayWidget.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WPushButton.h>
#include <Wt/WTimer.h>

#include "WebUIPluginLoader.h"
#include "ModuleWidgets/ModuleContainer.h"
#include <libDSP/include/DSPHost.h>
#include <libDSP/include/Modules/DSPModule.h>

ModularWebUI::ModularWebUI(const Wt::WEnvironment &env, DSPHost &app)
    : Wt::WApplication { env }
    , m_application { app }
{
  registerModule("DSPModule", [](DSPModule *module) {
    return std::make_unique<ModuleWidget>(module);
  });

  init();

  m_pluginLoader = std::make_unique<WebUIPluginLoader>(this);
}

void ModularWebUI::init()
{
  require("dom_helpers.js");
  root()->clear();

  m_domProxy = std::make_unique<WidgetDOMSizeProxy>(root());

  auto header = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  header->addWidget(std::make_unique<PlaygroundToolboxWidget>(this, &m_application));
  header->setStyleClass("header-container");
  header->setStyleClass("style-base");

  root()->setStyleClass("root-container");

  m_moduleContainer = dynamic_cast<ModuleContainer *>(
      root()->addWidget(std::make_unique<ModuleContainer>(m_application.getModules(), this)));

  m_overlay = root()->addWidget(std::make_unique<WireOverlayWidget>(&m_application, this));

  auto timer = root()->addChild(std::make_unique<Wt::WTimer>());
  timer->setSingleShot(false);
  timer->setInterval(std::chrono::milliseconds(250));
  timer->timeout().connect(m_overlay, &WireOverlayWidget::requestRedraw);
  timer->start();

  useStyleSheet("modular.css");
}

const WidgetDOMSizeProxy *ModularWebUI::getDomProxy() const
{
  return m_domProxy.get();
}

std::vector<Connection> ModularWebUI::getConnections()
{
  std::vector<Connection> ret {};

  auto &modules = m_application.getModules();
  for(auto &module : modules)
  {
    if(module)
      for(auto &in : module->getInputs())
      {
        if(auto src = in->connectedTo())
        {
          ret.emplace_back(Connection { src, in });
        }
      }
  }

  return ret;
}

ModuleContainer *ModularWebUI::getModuleContainer()
{
  return m_moduleContainer;
}

void ModularWebUI::registerModule(const std::string &modulename, ModularWebUI::tFactoryCB factoryCallback)
{
  m_moduleFactories[modulename] = std::move(factoryCallback);
}

ModularWebUI::tFactoryCB ModularWebUI::getFactory(DSPModule *module)
{
  try
  {
    return m_moduleFactories.at(module->getTypeName());
  }
  catch(...)
  {
    return nullptr;
  }
}

PluginLoader *ModularWebUI::getPluginLoader()
{
  return m_pluginLoader.get();
}
