#include <utility>

#include "libDSP/include/DSPHost.h"

DSPHost::DSPHost() {
    m_modules.reserve(100); //TODO use other container than vector, bugs waiting to happen here!!
};

void DSPHost::tick() {}

void DSPHost::onRemoveOutput(Output *o) {
  for (auto &module : m_modules) {
    if (module)
      for (auto &i : module->getInputs()) {
        i->tryDisconnect(o);
      }
  }
}

void DSPHost::registerModule(const char *name,
                             std::function<DSPModule *(DSPHost *)> factory) {
  m_moduleFactories[name] = std::move(factory);
}

DSPModule *DSPHost::createModule(const std::string &name) {
  auto it = m_moduleFactories.find(name);
  if (it != m_moduleFactories.end()) {
    auto ret = it->second(this);
    auto casted = static_cast<DSPModule *>(ret);
    m_modules.emplace_back(casted);
    return m_modules.back().get();
  }
  return nullptr;
}
std::vector<std::string> DSPHost::getAvailableModules() const {
  std::vector<std::string> ret{};
  for (auto &m : m_moduleFactories) {
    ret.emplace_back(m.first);
  }
  return ret;
}

void DSPHost::removeModule(DSPModule *me) {
  for (auto &mod : m_modules) {
    if (mod.get() == me) {
      mod.reset(nullptr);
    }
  }
}
