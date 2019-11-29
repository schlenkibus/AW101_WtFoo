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

  virtual DSPModule *createModule(const std::string &name);
  DSPModule *createRootModule(std::unique_ptr<DSPModule> &&module);

  void registerModule(const char *name, std::function<std::unique_ptr<DSPModule> && (DSPHost *)> factory);
  std::vector<std::string> getAvailableModules() const;

  DSPModule *findModuleByUuid(const LibUUID::UUID &uuid);
  void removeModule(DSPModule *me);

  void setDirty();

  const std::vector<DSPModule *> &getTickOrder() const;

 protected:
  std::map<std::string, std::function<std::unique_ptr<DSPModule> && (DSPHost *)>> m_moduleFactories;

  FacadeVector<DSPModule> m_modules;
  DSPModule *m_rootModule = nullptr;

  std::vector<DSPModule *> m_modulePtrsInTickOrder;

  void recalculateOrder();

  std::atomic<bool> m_dirty { true };

 private:
  bool isDeconstructing = false;
};