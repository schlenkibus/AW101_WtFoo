#pragma once
#include "../catch.hpp"
#include "libDSP/include/DSPHost.h"
#include "libDSP/include/Modules/DSPModule.h"

namespace TestHelper
{
  inline void removeModule(DSPHost* host, DSPModule* module)
  {
    auto moduleUUID = module->getUuid();
    host->markRemoved(module);
    host->tick();
    REQUIRE(host->findModuleByUuid(moduleUUID) == nullptr);
  }
}
