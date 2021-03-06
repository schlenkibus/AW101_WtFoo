#include <utility>
#include <set>
#include "libDSP/include/DSPHost.h"
#include <thread>

void DSPHost::tick()
{
  m_semaphore.s++;

  if(m_dirty)
    cleanDirty();

  for(auto module : m_modulePtrsInTickOrder)
  {
    module->tick();
  }

  m_semaphore.s--;
}

void DSPHost::registerModule(const char *name, tModuleFactoryCB factory)
{
  m_moduleFactories[name] = std::move(factory);
}

DSPModule *DSPHost::createModule(const std::string &name)
{
  do {
    std::this_thread::sleep_for(std::chrono::microseconds(100));
  } while(m_semaphore.s != 0);

  m_semaphore.s++;

  auto it = m_moduleFactories.find(name);
  if(it != m_moduleFactories.end())
  {
    auto ret = m_modules.emplace_back(it->second(this));
    m_semaphore.s--;
    return ret;
  }

  m_semaphore.s--;
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

  template <typename T, typename tContainer> bool contains(tContainer &container, const T &value)
  {
    for(auto &e : container)
      if(value == e)
        return true;
    return false;
  }

  void recurse(DSPModule *currentModule, std::vector<DSPModule *> &currentRecurseStack,
               std::vector<DSPModule *> &tickOrderReversed)
  {
    if(currentModule == nullptr)
      return;

    currentRecurseStack.emplace_back(currentModule);

    for(auto inputToCurrent : currentModule->getInputs())
    {
      if(auto predescessorOutput = inputToCurrent->connectedTo())
      {
        auto predeseccor = predescessorOutput->getParent();
        if(!contains(tickOrderReversed, predeseccor) && !contains(currentRecurseStack, predeseccor))
        {
          recurse(predeseccor, currentRecurseStack, tickOrderReversed);
        }
      }
    }

    currentRecurseStack.erase(std::remove_if(currentRecurseStack.begin(), currentRecurseStack.end(),
                                             [=](auto o) { return currentModule == o; }));

    if(!contains(tickOrderReversed, currentModule))
    {
      tickOrderReversed.emplace_back(currentModule);
    }
  }
}

void DSPHost::recalculateOrder()
{
  std::vector<DSPModule *> tickOrderReversed {};

  std::vector<DSPModule *> currentPredecessors {};

  algorithm::recurse(m_rootModule, currentPredecessors, tickOrderReversed);

  m_modulePtrsInTickOrder.assign(tickOrderReversed.begin(), tickOrderReversed.end());
  m_dirty = false;
}

void DSPHost::setDirty()
{
  m_dirty = true;
}

void DSPHost::cleanDirty()
{
  for(auto &i : m_removeQueue)
  {
    removeModule(i);
  }

  m_removeQueue.clear();

  recalculateOrder();

  m_dirty = false;
}

DSPModule *DSPHost::findModuleByUuid(const LibUUID::UUID &uuid)
{
  return m_modules.find([=](auto other) { return other->getUuid() == uuid; });
}

DSPHost::~DSPHost() = default;

const std::vector<DSPModule *> &DSPHost::getTickOrder() const
{
  return m_modulePtrsInTickOrder;
}

const std::vector<DSPModule *> &DSPHost::getModules() const
{
  return m_modules.getData();
}

PluginLoader *DSPHost::getPluginLoader()
{
  return m_libaryLoader.get();
}

void DSPHost::markRemoved(DSPModule *pModule)
{
  m_removeQueue.emplace_back(pModule);
  setDirty();
}

void DSPHost::cleanInput(DSPOutputNode *nowInvalid)
{
  auto moduleToDelete = nowInvalid->getParent();

  for(auto module : getModules())
  {
    if(module != moduleToDelete)
      for(auto i : module->getInputs())
      {
        if(i && i->connectedTo() == nowInvalid)
        {
          i->clearInput();
        }
      }
  }
}