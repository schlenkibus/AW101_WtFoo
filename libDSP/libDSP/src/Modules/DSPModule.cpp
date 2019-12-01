#include "libDSP/include/Modules/DSPModule.h"
#include "libDSP/include/DSPHost.h"
#include "libDSP/include/DSPInfo.h"

DSPModule::DSPModule(DSPHost *parent)
    : m_host { parent }
{
}

DSPModule::DSPModule(DSPModule &&other) noexcept
    : m_parameters { std::move(other.m_parameters) }
    , m_outputs { std::move(other.m_outputs) }
    , m_inputs { std::move(other.m_inputs) }
    , m_host { other.m_host }
    , m_uuid { other.m_uuid }
{
}

DSPModule::~DSPModule() = default;

void DSPModule::tick()
{
  tickInternals();
}

void DSPModule::setDirty() const
{
  m_host->setDirty();
}

DSPInputNode *DSPModule::createInput(const std::string &name)
{
  return m_inputs.emplace_back(this, name);
}

DSPOutputNode *DSPModule::createOutput(const std::string &name)
{
  return m_outputs.emplace_back(this, name);
}

Parameter *DSPModule::createParameter(const std::string &name, float init, float min, float max, int pre)
{
  return m_parameters.emplace_back(name, min, max, init, pre);
}

DSPOutputNode *DSPModule::findOutput(const std::string &nodeName)
{
  return m_outputs.find([=](auto other) { return other->getName() == nodeName; });
}

DSPInputNode *DSPModule::findInput(const std::string &nodeName)
{
  return m_inputs.find([=](auto other) { return other->getName() == nodeName; });
}

const DSPInputNode *DSPModule::findInput(const std::string &nodeName) const
{
  return m_inputs.find([=](auto other) { return other->getName() == nodeName; });
}

Parameter *DSPModule::findParameter(const std::string &parameterName)
{
  for(auto node : m_parameters)
  {
    if(node->name == parameterName)
      return node;
  }
  return nullptr;
}

DSPHost *DSPModule::getHost()
{
  return m_host;
}

const LibUUID::UUID &DSPModule::getUuid() const
{
  return m_uuid;
}

const std::vector<DSPInputNode *> &DSPModule::getInputs() const
{
  return m_inputs.getData();
}

const std::vector<DSPOutputNode *> &DSPModule::getOutputs() const
{
  return m_outputs.getData();
}

const std::vector<Parameter *> &DSPModule::getParameters() const
{
  return m_parameters.getData();
}

const char *DSPModule::getTypeName() const
{
  return "DSPModule";
}
