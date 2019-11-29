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
  using tModuleFactoryCB = std::function<DSPModule*(DSPHost*)>;

  DSPHost();
  ~DSPHost();
  virtual void tick();

  virtual DSPModule *createModule(const std::string &name);
  DSPModule *createRootModule(DSPModule* module);

  void registerModule(const char *name, tModuleFactoryCB factory);
  std::vector<std::string> getAvailableModules() const;

  DSPModule *findModuleByUuid(const LibUUID::UUID &uuid);
  void removeModule(DSPModule *me);

  void setDirty();

  const std::vector<DSPModule *> &getTickOrder() const;

 protected:
  std::map<std::string, tModuleFactoryCB> m_moduleFactories;

  FacadeVector<DSPModule> m_modules;
  DSPModule *m_rootModule = nullptr;

  std::vector<DSPModule *> m_modulePtrsInTickOrder;

  void recalculateOrder();

  std::atomic<bool> m_dirty { true };

 private:
  bool isDeconstructing = false;
};