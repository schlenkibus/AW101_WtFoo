#pragma once
#include <string>

class DSPOutputNode;
class DSPModule;

class DSPInputNode
{
 public:
  explicit DSPInputNode(DSPModule* parent, std::string name, float def = 0.0);
  DSPInputNode(const DSPInputNode&);
  const DSPOutputNode* connectedTo() const;
  void clearInput();
  void connect(const DSPOutputNode* node);

  float getSignal() const;
  const std::string& getName() const;

  friend DSPInputNode& operator<<(DSPInputNode& input, const DSPOutputNode* output);

  const DSPModule* getParent() const;

 protected:
  DSPModule* m_parent { nullptr };

  const DSPOutputNode* m_signalFrom;

  float signal = 0;
  const float defaultSignal;
  const std::string m_name;

  friend class DSPOutputNode;
};
