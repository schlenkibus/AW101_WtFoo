#include "DSPModule.h"
#include "../DSPNodes/DSPInfo.h"
#include "BangModule.h"

const char *DSPModule::TYPE() const {
  return "DSPModule";
}

const std::vector<Input> &DSPModule::getInputs() const {
  return m_inputs;
}

const std::vector<Output> &DSPModule::getOutputs() const {
  return m_outputs;
}

std::vector<Input> DSPModule::getInputs() {
  return std::vector<Input>(m_inputs);
}

std::vector<Output> DSPModule::getOutputs() {
  return std::vector<Output>(m_outputs);
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

const Input* DSPModule::createInput(const std::string &name) {
  return &m_inputs.emplace_back(Input{name, createNode<DSPInputNode>()});
}

const Output* DSPModule::createOutput(const std::string &name) {
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