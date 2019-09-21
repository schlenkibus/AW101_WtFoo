#include "DSPOutputNode.h"

void DSPOutputNode::feedSignal(float signal) {
  this->signal = signal;
}

void DSPOutputNode::tick() { }
