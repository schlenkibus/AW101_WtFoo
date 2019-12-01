#include "../../include/DSPNodes/DSPNode.h"
#include <iostream>

void DSPNode::reset()
{
  signal = 0;
}

void DSPNode::tick()
{
}

DSPNode::DSPNode()
    : m_uuid {}
{
}
