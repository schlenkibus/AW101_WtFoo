#include "../../include/DSPNodes/DSPOutputNode.h"

DSPOutputNode::DSPOutputNode(DSPModule* parent, std::string name)
    : m_name { std::move(name) }
    , m_parent { parent }
{
}

void DSPOutputNode::setSignal(float s)
{
  this->signal = s;
}

const std::string& DSPOutputNode::getName() const
{
  return m_name;
}

DSPModule* DSPOutputNode::getParent() const
{
  return m_parent;
}

float DSPOutputNode::getSignal() const
{
  return signal;
}
