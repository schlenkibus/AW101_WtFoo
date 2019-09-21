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

void DSPInputNode::connect(DSPOutputNode *node) {
  m_signalFrom = node;
}

void DSPInputNode::removeIngoingConnection() {
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
DSPOutputNode *DSPInputNode::connectedTo() {
  return m_signalFrom;
}
