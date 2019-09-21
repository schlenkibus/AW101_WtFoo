#include <utility>

#pragma once
#include "../DSPNodes/DSPContainer.h"
#include "../DSPNodes/DSPOutputNode.h"
#include "../misc/Countdown.h"
#include "Input.h"
#include "Output.h"

class DSPModule : public DSPContainer {
public:
  const char *TYPE() const override;

  bool connectToInput(const Output &ingoing, const Input &target);
  bool clearInput(const Input &inputToClear);

  const std::vector<Input> &getInputs() const;
  const std::vector<Output> &getOutputs() const;

  std::vector<Input> getInputs();
  std::vector<Output> getOutputs();

  Output *findOutput(const std::string &nodeName);
protected:
  const Input* createInput(const std::string &name);
  const Output* createOutput(const std::string &name);

private:
  std::vector<Input> m_inputs;
  std::vector<Output> m_outputs;
};
