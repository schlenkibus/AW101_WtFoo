#include <utility>

#pragma once
#include "Input.h"
#include "Output.h"
#include "Parameter.h"
#include "libDSP/include/DSPNodes/DSPContainer.h"
#include "libDSP/include/DSPNodes/DSPOutputNode.h"

class DSPHost;

class DSPModule : public DSPContainer {
public:
  explicit DSPModule(DSPHost *parent);
  ~DSPModule() override;
  const char *TYPE() const override;

  bool connectToInput(const Output &ingoing, const Input &target);
  bool clearInput(const Input &inputToClear);

  std::vector<Input *> getInputs();
  std::vector<Output *> getOutputs();
  std::vector<Parameter*> getParameters();

  Output *findOutput(const std::string &nodeName);
  Input *findInput(const std::string &nodeName);
  Parameter*findParameter(const std::string& parameterName);

protected:
  Input *createInput(const std::string &name);
  Output *createOutput(const std::string &name);
  Parameter*createParameter(const std::string& name, float init, float min, float max);

  std::vector<Input> m_inputs;
  std::vector<Output> m_outputs;
  std::vector<Parameter> m_parameters;
  DSPHost *m_host;
};
