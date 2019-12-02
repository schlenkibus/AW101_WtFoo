#include "ButtonModule.h"

ButtonModule::ButtonModule(DSPHost* parent)
    : DSPModule(parent)
{
  m_out = createOutput("Signal");
}

const char* ButtonModule::getTypeName() const
{
  return "button";
}

void ButtonModule::tickInternals()
{
  DSPModule::tickInternals();
  m_out->setSignal(m_active ? 1.0f : 0.0f);
}

void ButtonModule::setState(bool s)
{
  m_active.store(s, std::memory_order::memory_order_relaxed);
}
