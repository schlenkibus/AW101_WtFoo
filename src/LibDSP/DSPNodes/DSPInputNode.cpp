#include "DSPInputNode.h"

DSPInputNode::DSPInputNode(float def) : defaultSignal{def} {
}

void DSPInputNode::tick() {
  if(m_signalFrom) {
    signal = m_signalFrom->signal;
  } else {
    signal = defaultSignal;
  }
}

void DSPInputNode::connect(DSPNode *node) {
  m_signalFrom = node;
}

void DSPInputNode::remove() {
  m_signalFrom = nullptr;
}

void DSPInputNode::print(std::ostream &stream) const {
  DSPNode::print(stream);
  if(m_signalFrom != nullptr)
    stream << "\n\tInput from: " << *m_signalFrom << "\n";
}

const char *DSPInputNode::TYPE() const {
  return "DSPInputNode";
}