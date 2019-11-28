#pragma once
#include "../catch.hpp"
#include "libDSP/include/DSPHost.h"
#include "libDSP/include/Modules/DSPModule.h"

namespace TestHelper
{
  inline void removeModule(DSPHost* host, DSPModule* module)
  {
    auto moduleUUID = module->getUuid();
    host->removeModule(module);
    REQUIRE(host->findModuleByUuid(moduleUUID) == nullptr);
  }
}
