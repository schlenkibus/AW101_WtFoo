#include <utility>

#pragma once
#include "libDSP/include/DSPNodes/DSPContainer.h"
#include "libDSP/include/DSPNodes/DSPOutputNode.h"
#include "Input.h"
#include "Output.h"

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

  Output *findOutput(const std::string &nodeName);
  Input *findInput(const std::string &nodeName);

protected:
  Input *createInput(const std::string &name);
  Output *createOutput(const std::string &name);
  std::vector<Input> m_inputs;
  std::vector<Output> m_outputs;
  DSPHost *m_host;
};
