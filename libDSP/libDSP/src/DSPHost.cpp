#include <utility>

#include <utility>
#include <set>

#include "libDSP/include/DSPHost.h"

DSPHost::DSPHost() = default;
;

void DSPHost::tick()
{
  if(m_dirty)
    recalculateOrder();

  for(auto module : m_modulePtrsInTickOrder)
  {
    module->tick();
  }
}

void DSPHost::registerModule(const char *name, tModuleFactoryCB factory)
{
  m_moduleFactories[name] = std::move(factory);
}

DSPModule *DSPHost::createModule(const std::string &name)
{
  auto it = m_moduleFactories.find(name);
  if(it != m_moduleFactories.end())
  {
    auto mod = m_modules.emplace_back(it->second(this));
    setDirty();
    return mod;
  }
  return nullptr;
}

std::vector<std::string> DSPHost::getAvailableModules() const
{
  std::vector<std::string> ret {};
  for(auto &m : m_moduleFactories)
  {
    ret.emplace_back(m.first);
  }
  return ret;
}

void DSPHost::removeModule(DSPModule *me)
{
  m_modules.remove(me);
  setDirty();
}

DSPModule *DSPHost::createRootModule(DSPModule *module)
{
  m_rootModule = m_modules.emplace_front(module);
  setDirty();
  return m_rootModule;
}

namespace algorithm
{
  using tRecurseStep = std::pair<DSPModule *, std::set<DSPModule *>>;

  template <typename T> bool contains(std::set<T> &container, const T &value)
  {
    for(auto &e : container)
      if(value == e)
        return true;
    return false;
  }

  void recurse(DSPModule *currentModule, std::set<DSPModule *> &tickOrderReversed)
  {
    if(currentModule == nullptr)
      return;

    tickOrderReversed.insert(currentModule);

    for(auto inputToCurrent : currentModule->getInputs())
    {
      if(auto predescessorOutput = inputToCurrent->connectedTo())
      {
        auto predeseccor = predescessorOutput->getParent();
        if(!contains(tickOrderReversed, predeseccor))
          recurse(predeseccor, tickOrderReversed);
      }
    }
  }
}

void DSPHost::recalculateOrder()
{
  std::set<DSPModule *> calculateLater;
  algorithm::recurse(m_rootModule, calculateLater);
  m_modulePtrsInTickOrder.assign(calculateLater.rbegin(), calculateLater.rend());
  m_dirty = false;
}

void DSPHost::setDirty()
{
  recalculateOrder();
}

DSPModule *DSPHost::findModuleByUuid(const LibUUID::UUID &uuid)
{
  return m_modules.find([=](auto other) { return other->getUuid() == uuid; });
}

DSPHost::~DSPHost()
{
  isDeconstructing = true;
}
const std::vector<DSPModule *> &DSPHost::getTickOrder() const
{
  return m_modulePtrsInTickOrder;
}
