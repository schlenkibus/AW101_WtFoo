#include "MultiplyModule.h"

MultiplyModule::MultiplyModule() {
  createInput("A");
  createInput("B");
  out = createOutput("AxB");

  a = findInput("A");
  b = findInput("B");
}

void MultiplyModule::tick() {
  DSPContainer::tick();

  out->set(a->getSignal() * b->getSignal());
}

const char *MultiplyModule::TYPE() const { return "MultiplyModule"; }
