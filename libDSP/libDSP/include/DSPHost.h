#pragma once
#include "libDSP/include/Modules/DSPModule.h"
#include "libDSP/include/UUID/UUID.h"
#include <cstring>
#include <functional>
#include <list>
#include <map>
#include <atomic>
#include <libDSP/include/plugin/PluginLoader.h>

class Output;

class DSPHost
{
 public:
  using tModuleFactoryCB = std::function<DSPModule *(DSPHost *)>;

  DSPHost() = default;

  virtual ~DSPHost();

  virtual void tick();
  virtual DSPModule *createModule(const std::string &name);
  DSPModule *createRootModule(DSPModule *module);

  void registerModule(const char *name, tModuleFactoryCB factory);
  std::vector<std::string> getAvailableModules() const;
  const std::vector<DSPModule *> &getModules() const;

  DSPModule *findModuleByUuid(const LibUUID::UUID &uuid);
  void removeModule(DSPModule *me);

  void setDirty();

  const std::vector<DSPModule *> &getTickOrder() const;

  template <typename LibraryLoader> void createLibraryLoader()
  {
    m_libaryLoader = std::make_unique<LibraryLoader>(this);
  }

  PluginLoader *getPluginLoader();

 protected:
  void recalculateOrder();

 private:
  std::map<std::string, tModuleFactoryCB> m_moduleFactories;

  DSPModule *m_rootModule = nullptr;
  FacadeVector<DSPModule> m_modules;
  std::vector<DSPModule *> m_modulePtrsInTickOrder;

  std::atomic<bool> m_dirty { true };

  std::unique_ptr<PluginLoader> m_libaryLoader;
};