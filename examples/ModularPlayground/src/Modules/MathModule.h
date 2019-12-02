#pragma once
#include <libDSP/include/Modules/DSPModule.h>
#include <functional>

class MathModule : public DSPModule
{
 public:
  template <typename tCB>
  MathModule(const char* name, DSPHost* host, tCB cb)
      : DSPModule(host)
      , m_cb { std::move(cb) }
  {
    x = createInput("X");
    y = createInput("Y");
    out = createOutput("=");
  }

  void tickInternals() override
  {
    out->setSignal(m_cb(x->getSignal(), y->getSignal()));
  }

 private:
  DSPInputNode* x;
  DSPInputNode* y;

  DSPOutputNode* out;

  std::function<float(float, float)> m_cb;
};
