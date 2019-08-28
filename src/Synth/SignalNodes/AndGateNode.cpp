#include "AndGateNode.h"

void AndGateNode::tick() {
}

void AndGateNode::setA(bool a) {
  inputA = a;
  signal = inputA && inputB;
}

void AndGateNode::setB(bool b) {
  inputB = b;
  signal = inputA && inputB;
}
