#pragma once
#include "../ModularPlaygroundApplication.h"
#include "ModuleWidgets/ModuleWidget.h"
#include <Wt/WApplication.h>
#include <examples/ModularPlayground/src/Modules/Connection.h>

class ModuleContainer;
class WireOverlayWidget;

namespace detail {
template <class T>
void traverseContainer(const std::function<void(T *)> &cb,
                       Wt::WContainerWidget *container) {
  for (auto &w : container->children()) {
    if (auto c = dynamic_cast<Wt::WContainerWidget *>(w)) {
      traverseContainer(cb, c);
    } else if (auto t = dynamic_cast<T *>(w)) {
      cb(t);
    }
  }
}
} // namespace detail

class ModularWebUI : public Wt::WApplication {
public:
  ModularWebUI(const Wt::WEnvironment &env, ModularPlaygroundApplication &app);
  void init();

  template <class T>
  void traverseAllWidgets(const std::function<void(T *)> &cb) {
    detail::traverseContainer<T>(cb, root());
  }

  std::vector<Connection> getConnections();

  std::vector<ModuleWidget *> getModuleWidgets();
  ModuleContainer* getModuleContainer();
  const WidgetDOMSizeProxy* getDomProxy() const;
protected:
  std::unique_ptr<WidgetDOMSizeProxy> m_domProxy;
  Wt::JavaScriptScope m_javascriptScope;
  ModuleContainer *m_moduleContainer;
  WireOverlayWidget *m_overlay;
  ModularPlaygroundApplication &m_application;
};
