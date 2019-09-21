#include "DSPModule.h"
#include "../DSPInfo.h"

const char *DSPModule::TYPE() const {
  return "DSPModule";
}

std::vector<Input*> DSPModule::getInputs() {
  std::vector<Input*> ret;
  for(auto& i: m_inputs)
    ret.emplace_back(&i);
  return ret;
}

std::vector<Output*> DSPModule::getOutputs() {
  std::vector<Output*> ret;
  for(auto& i: m_outputs)
    ret.emplace_back(&i);
  return ret;
}

bool DSPModule::connectToInput(const Output &ingoing, const Input& target) {
  for(auto& i: m_inputs) {
    if(i == target) {
      if(target.node && ingoing.node) {
        target.node->connect(ingoing.node);
        return true;
      }
    }
  }
  return false;
}

Input *DSPModule::createInput(const std::string &name) {
  return &m_inputs.emplace_back(Input{name, createNode<DSPInputNode>()});
}

Output *DSPModule::createOutput(const std::string &name) {
  return &m_outputs.emplace_back(Output{name, createNode<DSPOutputNode>()});
}
bool DSPModule::clearInput(const Input &inputToClear) {
  for(auto& i: m_inputs) {
    if(i == inputToClear)
      i.node->remove();
  }
  return false;
}

Output *DSPModule::findOutput(const std::string &nodeName) {
  for(auto& node: m_outputs) {
    if(node.name == nodeName)
      return &node;
  }
  return nullptr;
}