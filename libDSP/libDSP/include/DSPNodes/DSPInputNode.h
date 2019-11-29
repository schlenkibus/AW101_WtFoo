#pragma once

#include "DSPOutputNode.h"

class DSPInputNode
{
 public:
  explicit DSPInputNode(std::string name, float def = 0.0);
  DSPInputNode(const DSPInputNode&);
  void connect(const DSPOutputNode* node);
  const DSPOutputNode* connectedTo() const;
  void clearInput();

  float getSignal() const;
  const std::string& getName() const;

 protected:
  const DSPOutputNode* m_signalFrom;

  float signal = 0;
  const float defaultSignal;
  const std::string m_name;
};
