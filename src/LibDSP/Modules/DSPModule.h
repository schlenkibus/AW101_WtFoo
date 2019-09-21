#include <utility>

#pragma once
#include "../../LibDSP/Modules/DSPModule.h"
#include "../../Mixer/Audio/DrumKit.h"
#include "../DSPNodes/DSPContainer.h"
#include "../DSPNodes/DSPOutputNode.h"
#include "Input.h"
#include "Output.h"

class DSPModule : public DSPContainer {
public:
  const char *TYPE() const override;

  bool connectToInput(const Output &ingoing, const Input &target);
  bool clearInput(const Input &inputToClear);

  std::vector<Input*> getInputs();
  std::vector<Output*> getOutputs();

  Output *findOutput(const std::string &nodeName);
  Input* findInput(const std::string &nodeName);
protected:
  Input * createInput(const std::string &name);
  Output * createOutput(const std::string &name);
  std::vector<Input> m_inputs;
  std::vector<Output> m_outputs;
};
