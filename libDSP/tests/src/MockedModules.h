#pragma once
#include "libDSP/include/Modules/DSPModule.h"

namespace TestModules
{
  class OneTickDelay : public DSPModule
  {
   public:
    OneTickDelay(DSPHost* parent)
        : DSPModule(parent)
    {
      createInput("IN");
      createOutput("OUT");
    };

    const char* getName() override
    {
      return "OneTickDelay";
    }

    void tick() override
    {
      DSPContainer::tick();

      findOutput("OUT")->set(value);
      value = findInput("IN")->getSignal();
    }

    float getValue() const
    {
      return value;
    }

   private:
    float value {};
  };
}