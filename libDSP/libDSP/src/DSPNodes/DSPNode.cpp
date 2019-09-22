#include "../../include/DSPNodes/DSPNode.h"
#include <iostream>

void DSPNode::reset() { signal = 0; }

DSPNode::DSPNode() : m_uuid{} {}

void DSPNode::print(std::ostream &stream) const {
  stream << TYPE() << " " << m_uuid << " SIGNAL: " << signal << "\n";
}
