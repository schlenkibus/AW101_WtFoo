#pragma once
#include "ModuleWidgets/ModuleWidget.h"
#include <Wt/WApplication.h>
#include <libDSP/include/plugin/PluginLoader.h>
#include "GenericWidgets/WidgetDOMSizeProxy.h"
#include "NodeWidgets/Connection.h"
#include "libFilesystem/include/Directory.h"

class ModuleContainer;
class WireOverlayWidget;
class DSPHost;

namespace detail
{
  template <class T> void traverseContainer(const std::function<void(T *)> &cb, Wt::WContainerWidget *container)
  {
    for(auto &w : container->children())
    {
      if(auto c = dynamic_cast<Wt::WContainerWidget *>(w))
      {
        traverseContainer(cb, c);
      }
      else if(auto t = dynamic_cast<T *>(w))
      {
        cb(t);
      }
    }
  }
}

class ModularWebUI : public Wt::WApplication
{
 public:
  using tFactoryCB = std::function<std::unique_ptr<ModuleWidget>(DSPModule *)>;

  ModularWebUI(const Wt::WEnvironment &env, DSPHost &app);
  void init();

  std::vector<Connection> getConnections();

  ModuleContainer *getModuleContainer();
  const WidgetDOMSizeProxy *getDomProxy() const;

  void registerModule(const std::string &modulename, tFactoryCB factoryCallback);
  tFactoryCB getFactory(DSPModule *module);

  PluginLoader *getPluginLoader();

 protected:
  std::unique_ptr<PluginLoader> m_pluginLoader;
  std::unordered_map<std::string, tFactoryCB> m_moduleFactories;
  std::unique_ptr<WidgetDOMSizeProxy> m_domProxy;
  Wt::JavaScriptScope m_javascriptScope;
  ModuleContainer *m_moduleContainer;
  WireOverlayWidget *m_overlay;
  DSPHost &m_application;
};
