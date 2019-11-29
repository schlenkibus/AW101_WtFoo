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

  class EquationModule : public DSPModule
  {
   public:
    template <typename tCB>
    EquationModule(tCB cb, DSPHost* h)
        : DSPModule(h)
        , m_cb { cb }
    {
      createInput("X");
      createInput("Y");

      createOutput("=");
    }
    const char* getName() override
    {
      return "equasion";
    }

    void tick() override
    {
      DSPContainer::tick();
      findOutput("=")->set(m_cb(findInput("X")->getSignal(), findInput("Y")->getSignal()));
    }

   private:
    std::function<float(float, float)> m_cb;
  };

  class TestRootModule : public DSPModule
  {
   public:
    explicit TestRootModule(DSPHost* host)
        : DSPModule(host)
    {
      createInput("IN");
    }
    const char* getName() override
    {
      return "TestRoot";
    }
    float getValue() const
    {
      return findInput("IN")->getSignal();
    }
  };

  class NumberModule : public DSPModule
  {
   public:
    explicit NumberModule(DSPHost* parent)
        : DSPModule(parent)
    {
      createOutput("OUT");
    }

    const char* getName() override
    {
      return "Number";
    }

    void setValue(float number)
    {
      findOutput("OUT")->set(number);
    }
  };
}