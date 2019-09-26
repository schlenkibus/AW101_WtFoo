#pragma once
#include "../ModularPlaygroundApplication.h"
#include <Wt/WApplication.h>
#include "ModuleWidgets/ModuleWidget.h"

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
}

class ModularWebUI : public Wt::WApplication {
public:
    ModularWebUI(const Wt::WEnvironment &env, ModularPlaygroundApplication &app, const char* basePath);
    void init();

    float getWindowX() const;
    float getWindowY() const;

    template<class T>
    void traverseAllWidgets(const std::function<void(T*)>& cb) {
        detail::traverseContainer<T>(cb, root());
    }
  protected:
    ModularPlaygroundApplication &m_application;
};
