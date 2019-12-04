#include "NumberModule.h"

NumberModule::NumberModule(DSPHost* host)
    : DSPModule(host)
{
  m_out = createOutput("Number");
}

const char* NumberModule::getTypeName() const
{
  return "NumberModule";
}

void NumberModule::tickInternals()
{
  if(m_out->getSignal() != m_number)
    m_out->setSignal(m_number);
}

void NumberModule::setNumber(float number)
{
  m_number = number;
}