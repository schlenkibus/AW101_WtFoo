#pragma once
#include "DSPNode.h"
#include "DSPInputNode.h"

class DSPModule;

class DSPOutputNode
{
 public:
  explicit DSPOutputNode(DSPModule* parent, std::string name);
  ~DSPOutputNode();
  void setSignal(float signal);
  float getSignal() const;
  const std::string& getName() const;
  DSPModule* getParent() const;

  friend DSPOutputNode& operator<<(DSPOutputNode& output, DSPInputNode* input)
  {
    input->connect(&output);
    return output;
  }

 private:
  DSPModule* m_parent{nullptr};
  std::string m_name;
  float signal{0.0};
};
