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
      , m_name{name}
  {
    x = createInput("X");
    y = createInput("Y");
    out = createOutput("=");
  }

  const char* getTypeName() const override
  {
    return m_name.c_str();
  }

  void tickInternals() override
  {
    out->setSignal(m_cb(x->getSignal(), y->getSignal()));
  }

 private:
  DSPInputNode* x;
  DSPInputNode* y;

  DSPOutputNode* out;

  const std::string m_name;

  std::function<float(float, float)> m_cb;
};
