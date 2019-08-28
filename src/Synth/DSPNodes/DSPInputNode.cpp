#include "DSPInputNode.h"

DSPSignalIndex DSPInputNode::addInput() {
  auto& item = m_inputs.emplace_back();
  item.m_active = true;
  item.m_leftSample = 0;
  item.m_rightSample = 0;
  return m_inputs.size() - 1;
}

void DSPInputNode::setSignal(DSPSignalIndex index, float l, float r) {
  if(auto item = getItem(index)) {
    item->m_leftSample = l;
    item->m_rightSample = r;
  }
}
void DSPInputNode::disconnect(DSPSignalIndex index) {
  if(auto item = getItem(index)) {
    item->m_active = false;
  }
}

DSPInputNode::Input *DSPInputNode::getItem(DSPSignalIndex index) {
  if(index < m_inputs.size())
    return &m_inputs[index];
  return nullptr;
}


template<class T>
float getAverageForItemCollection(const std::vector<T>& inputs, bool returnLeft) {

  float left = 0.0f;
  float right = 0.0f;

  int numActive = 0;

  for(auto& item: inputs) {
    if(item.m_active)
    {
      right += item.m_rightSample;
      left += item.m_leftSample;
      numActive++;
    }
  }

  return (returnLeft ? left : right) / numActive;
}

void DSPInputNode::tick() {
  auto sig = (getAverageForItemCollection(m_inputs, true) + getAverageForItemCollection(m_inputs, false)) / 2.0f;
  signal = sig != sig ? signal : sig;
}
