#include "../../include/DSPNodes/DSPNode.h"
#include <iostream>

void DSPNode::reset() { signal = 0; }

DSPNode::DSPNode() : m_uuid{} {}
