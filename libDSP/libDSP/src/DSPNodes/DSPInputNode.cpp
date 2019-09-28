#include "../../include/DSPNodes/DSPInputNode.h"

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
  signal = defaultSignal;
}

DSPOutputNode *DSPInputNode::connectedTo() {
  return m_signalFrom;
}
