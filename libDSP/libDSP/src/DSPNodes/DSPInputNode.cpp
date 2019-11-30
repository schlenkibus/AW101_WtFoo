#include <utility>
#include "../../include/DSPNodes/DSPInputNode.h"
#include "../../include/Modules/DSPModule.h"

DSPInputNode::DSPInputNode(DSPModule *parent, std::string name, float def)
    : defaultSignal { def }
    , m_name { std::move(name) }
    , m_signalFrom { nullptr }
    , m_parent { parent }
{
  signal = def;
}

DSPInputNode::DSPInputNode(const DSPInputNode &other)
    : defaultSignal { other.defaultSignal }
    , m_signalFrom { other.m_signalFrom }
    , signal { other.signal }
{
}

void DSPInputNode::clearInput()
{
  m_signalFrom = nullptr;
  signal = defaultSignal;
}

const std::string &DSPInputNode::getName() const
{
  return m_name;
}

const DSPOutputNode *DSPInputNode::connectedTo() const
{
  return m_signalFrom;
}

void DSPInputNode::connect(const DSPOutputNode *node)
{
  m_signalFrom = node;
  m_parent->setDirty();
}

float DSPInputNode::getSignal() const
{
  if(m_signalFrom)
    return m_signalFrom->getSignal();
  else
    return defaultSignal;
}

DSPInputNode &operator<<(DSPInputNode &input, const DSPOutputNode *output)
{
  input.connect(output);
  return input;
}
