#pragma once
#include "../DSPNodes/DSPOutputNode.h"

class Output {
public:
  Output(std::string na, DSPOutputNode *no) : name{std::move(na)}, node{no} {}
  std::string name;
  friend bool operator==(const Output &lhs, const Output &rhs) {
    return lhs.name == rhs.name;
  }

  void set(float signal) const { node->feedSignal(signal); }

private:
  DSPOutputNode *node;

  friend class DSPModule;
  friend class Input;
};
