#include <utility>
#include <malloc.h>

#include "libDSP/include/DSPHost.h"

DSPHost::DSPHost() = default;
;

void DSPHost::tick()
{
  if(m_dirty)
  {
    recalculateOrder();
    m_dirty = false;
  }

  for(auto module : m_modulePtrsInTickOrder)
  {
    module->tick();
  }
}

void DSPHost::onRemoveOutput(Output *o)
{
  for(auto &module : m_modules)
  {
    if(module)
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

DSPModule *DSPHost::createModule(std::unique_ptr<DSPModule> &&module)
{
  m_modules.emplace_back(std::move(module));
  setDirty();
  return m_modules.back().get();
}

namespace algorithm
{
  using tRecurseStep = std::pair<DSPModule *, std::vector<DSPModule *>>;

  template <typename T> bool contains(std::vector<T> &container, const T &value)
  {
    for(auto &e : container)
      if(value == e)
        return true;
    return false;
  }

  void recurse(DSPModule *currentModule, std::vector<DSPModule *> &tickOrderReversed)
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
      tickOrderReversed.emplace_back(currentModule);
  }
}

void DSPHost::recalculateOrder()
{
  std::vector<DSPModule *> calculateLater;
  auto &firstModule = *m_modules.begin();
  if(firstModule)
  {
    algorithm::recurse(firstModule.get(), calculateLater);
  }

  m_modulePtrsInTickOrder = std::vector<DSPModule *> { calculateLater.rbegin(), calculateLater.rend() };
}

void DSPHost::setDirty()
{
  m_dirty = true;
}
