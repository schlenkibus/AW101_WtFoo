#include "DSPOutputNode.h"
#include "DSPInputNode.h"

void DSPOutputNode::tick() {
  for(auto& outputs: m_outputs) {
    outputs.m_node->setSignal(outputs.m_index, signal, signal);
  }
}

void DSPOutputNode::connectTo(DSPInputNode *node) {
  m_outputs.emplace_back(node);
}

void DSPOutputNode::disconnectFrom(DSPInputNode *node) {
  for(auto& o: m_outputs) {
    if(node == o.m_node)
      node->disconnect(o.m_index);
  }
}

DSPOutputNode::OutputPair::OutputPair(DSPInputNode *node) {
  m_node = node;
  m_index = m_node->addInput();
}
