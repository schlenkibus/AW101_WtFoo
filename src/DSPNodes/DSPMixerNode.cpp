#include "DSPMixerNode.h"
#include <algorithm>
#include <iostream>

void DSPMixerNode::connect(DSPNode *node) { m_inputs.emplace_back(node); }

void DSPMixerNode::remove(DSPNode *node) {
  try {
    m_inputs.erase(std::remove(m_inputs.begin(), m_inputs.end(), node),
                   m_inputs.end());
  } catch (...) {
    std::cerr << "could not remove DSPNode: " << node->m_uuid
              << " from input node: " << m_uuid << std::endl;
  }
}

void DSPMixerNode::tick() {
  if (m_inputs.empty()) {
    signal = 0.0;
  } else {
    decltype(signal) temp = 0;
    for (auto &i : m_inputs) {
      i->tick();
      temp += i->signal;
    }
    signal = temp / m_inputs.size();
  }
}
