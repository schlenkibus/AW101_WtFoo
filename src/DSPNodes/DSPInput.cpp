#include "DSPInput.h"

DSPInput::DSPInput(float def) : defaultSignal{def} {
}

void DSPInput::tick() {
  if(auto* ptr = m_signalFrom) {
    signal = ptr->signal;
  } else {
    signal = defaultSignal;
  }
}

void DSPInput::connect(DSPNode *node) {
  m_signalFrom = node;
}

void DSPInput::remove(const DSPNode* node) {
  m_signalFrom = nullptr;
}

void DSPInput::print(std::ostream &stream) const {
  DSPNode::print(stream);
  if(m_signalFrom != nullptr)
    stream << "\n\tInput from: " << *m_signalFrom << "\n";
}

const char *DSPInput::TYPE() const {
  return "INPUT";
}