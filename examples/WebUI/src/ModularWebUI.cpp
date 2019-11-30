#include "ModularWebUI.h"

#include "ModuleWidgets/BangButtonModuleWidget.h"
#include "NodeWidgets/DSPInputWidget.h"
#include "PlaygroundToolboxWidget.h"
#include "WireOverlayWidget.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WPushButton.h>
#include <Wt/WTimer.h>

#include "ModuleWidgets/ModuleContainer.h"
#include <libDSP/include/DSPHost.h>

ModularWebUI::ModularWebUI(const Wt::WEnvironment &env, DSPHost &app)
    : Wt::WApplication { env }
    , m_application { app }
{
  init();
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
      root()->addWidget(std::make_unique<ModuleContainer>(m_application.getModules())));

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

void ModularWebUI::loadPlugins(const Directory &d)
{
  for(auto &file : d.getFiles())
  {
    try
    {
      m_application.getPluginLoader()->loadPlugin(file);
    }
    catch(...)
    {
      std::cerr << "could not load plugins from file " << file.getAbsoulutePath() << "\n";
    }
  }
}