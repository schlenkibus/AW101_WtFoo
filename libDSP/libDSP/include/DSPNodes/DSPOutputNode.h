#pragma once
#include "DSPNode.h"

class DSPModule;

class DSPOutputNode
{
 public:
  explicit DSPOutputNode(DSPModule* parent, std::string name);
  void setSignal(float signal);
  float getSignal() const;
  const std::string& getName() const;
  DSPModule* getParent() const;

 private:
  DSPModule* m_parent;
  std::string m_name;
  float signal;
};
