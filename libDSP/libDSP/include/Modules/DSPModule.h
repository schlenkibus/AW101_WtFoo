#include <utility>
#pragma once

#include "Parameter.h"
#include <libDSP/include/DSPNodes/DSPInputNode.h>
#include <libDSP/include/DSPNodes/DSPContainer.h>
#include <libDSP/include/DSPNodes/DSPOutputNode.h>
#include <libDSP/include/misc/FacadeVector.h>

class DSPHost;

class DSPModule
{
 public:
  explicit DSPModule(DSPHost *parent);
  virtual ~DSPModule();

  const std::vector<DSPInputNode *> &getInputs() const;
  const std::vector<DSPOutputNode *> &getOutputs() const;
  const std::vector<Parameter *> &getParameters() const;

  DSPOutputNode *findOutput(const std::string &nodeName);
  DSPInputNode *findInput(const std::string &nodeName);
  const DSPInputNode *findInput(const std::string &nodeName) const;
  Parameter *findParameter(const std::string &parameterName);

  DSPHost *getHost();
  const LibUUID::UUID &getUuid() const;

  virtual const char *getName() = 0;

  void tick();

  /*
   * has to take care of setting the outputs
   */
  virtual void tickInternals() = 0;

 protected:
  const LibUUID::UUID m_uuid;
  DSPInputNode *createInput(const std::string &name);
  DSPOutputNode *createOutput(const std::string &name);
  Parameter *createParameter(const std::string &name, float init, float min, float max, int pre = 3);

  FacadeVector<DSPInputNode> m_inputs;
  FacadeVector<DSPOutputNode> m_outputs;
  FacadeVector<Parameter> m_parameters;
  DSPHost *m_host;
};
