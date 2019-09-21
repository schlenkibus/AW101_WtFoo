#include "DSPMixerNode.h"
#include <algorithm>
#include <iostream>

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
