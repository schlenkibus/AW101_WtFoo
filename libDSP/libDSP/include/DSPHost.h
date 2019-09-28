#pragma once
#include "libDSP/include/Modules/DSPModule.h"
#include <functional>
#include <map>

class Output;

class DSPHost {
public:
  DSPHost();
  virtual void tick();
  void onRemoveOutput(Output *o);

  DSPModule *createModule(const std::string &name);
  void registerModule(const char* name, std::function<DSPModule*(DSPHost*)> factory);
  std::vector<std::string> getAvailableModules() const;

  void removeModule(DSPModule* me);

protected:
  std::map<std::string, std::function<DSPModule*(DSPHost*)>> m_moduleFactories;
  std::vector<std::unique_ptr<DSPModule>> m_modules;
};