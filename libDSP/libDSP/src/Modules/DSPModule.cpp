#include "libDSP/include/Modules/DSPModule.h"
#include "libDSP/include/DSPHost.h"
#include "libDSP/include/DSPInfo.h"

DSPModule::DSPModule(DSPHost *parent)
    : m_host { parent }
{
}

DSPModule::~DSPModule()
{
}

std::vector<Input *> DSPModule::getInputs()
{
  std::vector<Input *> ret;
  for(auto &i : m_inputs)
    ret.emplace_back(&i);
  return ret;
}

std::vector<Output *> DSPModule::getOutputs()
{
  std::vector<Output *> ret;
  for(auto &i : m_outputs)
    ret.emplace_back(&i);
  return ret;
}

std::vector<Parameter *> DSPModule::getParameters()
{
  std::vector<Parameter *> ret;
  for(auto &i : m_parameters)
    ret.emplace_back(&i);
  return ret;
}

Input *DSPModule::createInput(const std::string &name)
{
  m_inputs.emplace_back(Input { name, createNode<DSPInputNode>(), this });
  return &m_inputs.back();
}

Output *DSPModule::createOutput(const std::string &name)
{
  m_outputs.emplace_back(Output { this, name, createNode<DSPOutputNode>() });
  return &m_outputs.back();
}

Parameter *DSPModule::createParameter(const std::string &name, float init, float min, float max, int pre)
{
  m_parameters.emplace_back(Parameter { name, min, max, init, pre });
  return &m_parameters.back();
}

Output *DSPModule::findOutput(const std::string &nodeName)
{
  for(auto &node : m_outputs)
  {
    if(node.name == nodeName)
      return &node;
  }
  return nullptr;
}

Input *DSPModule::findInput(const std::string &nodeName)
{
  for(auto &node : m_inputs)
  {
    if(node.name == nodeName)
      return &node;
  }
  return nullptr;
}

Parameter *DSPModule::findParameter(const std::string &parameterName)
{
  for(auto &node : m_parameters)
  {
    if(node.name == parameterName)
      return &node;
  }
  return nullptr;
}

void DSPModule::disconnectNodes(Input *pInput)
{
  for(auto &i : m_inputs)
    if(&i == pInput)
    {
      pInput->tryDisconnect(pInput->connectedTo());
    }

  getHost()->setDirty();
}

DSPHost *DSPModule::getHost()
{
  return m_host;
}