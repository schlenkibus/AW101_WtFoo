#pragma once
#include "libDSP/include/Modules/DSPModule.h"
#include "libDSP/include/UUID/UUID.h"
#include <cstring>
#include <functional>
#include <list>
#include <map>
#include <atomic>

class Output;

class DSPHost
{
 public:
  DSPHost();
  ~DSPHost();
  virtual void tick();
  void onRemoveOutput(Output *o);

  virtual DSPModule *createModule(const std::string &name);
  DSPModule *createRootModule(std::unique_ptr<DSPModule> &&module);

  void registerModule(const char *name, std::function<DSPModule *(DSPHost *)> factory);
  std::vector<std::string> getAvailableModules() const;

  DSPModule *findModuleByUuid(const LibUUID::UUID &uuid);
  void removeModule(DSPModule *me);

  void setDirty();

  const std::vector<DSPModule*>& getTickOrder() const;

 protected:
  std::map<std::string, std::function<DSPModule *(DSPHost *)>> m_moduleFactories;

  DSPModule* m_rootModule = nullptr;
  std::list<std::unique_ptr<DSPModule>> m_modules;
  std::vector<DSPModule *> m_modulePtrsInTickOrder;

  void recalculateOrder();

  std::atomic<bool> m_dirty { true };
 private:
  bool isDeconstructing = false;
};