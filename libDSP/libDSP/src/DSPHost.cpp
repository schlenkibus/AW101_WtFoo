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

void DSPHost::onRemoveOutput(Output *o)
{
  if(isDeconstructing)
    return;

  for(auto &module : m_modules)
  {
    if(module && module.get() != o->getModule())
      for(auto &i : module->getInputs())
      {
        i->tryDisconnect(o);
      }
  }

  setDirty();
}

void DSPHost::registerModule(const char *name, std::function<DSPModule *(DSPHost *)> factory)
{
  m_moduleFactories[name] = std::move(factory);
}

DSPModule *DSPHost::createModule(const std::string &name)
{
  auto it = m_moduleFactories.find(name);
  if(it != m_moduleFactories.end())
  {
    auto ret = it->second(this);
    auto casted = static_cast<DSPModule *>(ret);
    m_modules.emplace_back(casted);
    setDirty();
    return m_modules.back().get();
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
  for(auto &mod : m_modules)
  {
    if(mod.get() == me)
    {
      mod.reset(nullptr);
    }
  }

  setDirty();
}

DSPModule *DSPHost::createRootModule(std::unique_ptr<DSPModule> &&module)
{
  m_modules.emplace_front(std::move(module));
  m_rootModule = m_modules.begin()->get();
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

    for(auto inputToCurrent : currentModule->getInputs())
    {
      if(auto predescessorOutput = inputToCurrent->connectedTo())
      {
        auto predeseccor = predescessorOutput->getModule();
        recurse(predeseccor, tickOrderReversed);
      }
    }

    if(!contains(tickOrderReversed, currentModule))
      tickOrderReversed.insert(currentModule);
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
  for(auto &m : m_modules)
  {
    if(m && m->getUuid() == uuid)
    {
      return m.get();
    }
  }
  return nullptr;
}

DSPHost::~DSPHost()
{
  isDeconstructing = true;
}
const std::vector<DSPModule *> &DSPHost::getTickOrder() const
{
  return m_modulePtrsInTickOrder;
}
