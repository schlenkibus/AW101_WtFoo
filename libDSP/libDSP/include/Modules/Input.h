#pragma once
#include "libDSP/include/DSPNodes/DSPInputNode.h"

class DSPModule;
class Output;

class Input
{
 public:
  Input(std::string na, DSPInputNode *no, DSPModule *parent)
      : name { std::move(na) }
      , node { no }
      , m_connectedTo { nullptr }
      , parent { parent }
  {
  }

  friend bool operator==(const Input &lhs, const Input &rhs)
  {
    return lhs.name == rhs.name;
  }

  float getSignal() const;

  void connect(Output *o);
  void tryDisconnect(Output *o);
  void tick();
  Output *connectedTo();

  const LibUUID::UUID &getUUID() const;

  const std::string &getName() const
  {
    return name;
  }

 private:
  std::string name;

  DSPModule *parent;
  DSPInputNode *node;
  Output *m_connectedTo;

  friend class DSPModule;
  friend class Output;
};