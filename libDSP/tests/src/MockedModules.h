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

    void tickInternals() override
    {
      findOutput("OUT")->setSignal(value);
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

      findOutput("=")->setSignal(0);
    }

    void tickInternals() override
    {
      findOutput("=")->setSignal(m_cb(findInput("X")->getSignal(), findInput("Y")->getSignal()));
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

    void setValue(float number)
    {
      findOutput("OUT")->setSignal(number);
    }
  };
}