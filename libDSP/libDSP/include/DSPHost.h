#pragma once
#include "libDSP/include/Modules/DSPModule.h"

class Output;

class DSPHost {
public:
  DSPHost();
  virtual void tick();
  void onRemoveOutput(Output &o);
  template <class tModule, typename... tArgs>

  tModule *createModule(tArgs... args) {
    auto ret = dynamic_cast<tModule *>(
        m_modules.emplace_back(std::make_unique<tModule>(args...)).get());
    return ret;
  }

protected:
  std::vector<std::unique_ptr<DSPModule>> m_modules;
};
