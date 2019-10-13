#pragma once
#include "libDSP/include/Modules/DSPModule.h"
#include "libDSP/include/UUID/UUID.h"
#include <cstring>
#include <functional>
#include <map>

class Output;

class DSPHost {
public:
  DSPHost();
  virtual void tick();
  void onRemoveOutput(Output *o);

  virtual DSPModule *createModule(const std::string &name);
  virtual DSPModule* createModule(std::unique_ptr<DSPModule>&& module);

  template <class T> T *findModule(const char *name) {
    for (auto &m : m_modules) {
      if (strcmp(m->getName(), name) == 0) {
        if (auto t = dynamic_cast<T *>(m.get()))
          return t;
      }
    }
    return nullptr;
  }

  void registerModule(const char *name,
                      std::function<DSPModule *(DSPHost *)> factory);
  std::vector<std::string> getAvailableModules() const;

  void removeModule(DSPModule *me);

protected:
  std::map<std::string, std::function<DSPModule *(DSPHost *)>>
      m_moduleFactories;
  std::vector<std::unique_ptr<DSPModule>> m_modules;
};