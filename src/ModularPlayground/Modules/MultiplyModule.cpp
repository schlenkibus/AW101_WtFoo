#include "MultiplyModule.h"

MultiplyModule::MultiplyModule() {
  a = createInput("A");
  b = createInput("B");
  out = createOutput("AxB");
}

void MultiplyModule::tick() {
  DSPContainer::tick();

  out->set(a->getSignal() * b->getSignal());
}
const char *MultiplyModule::TYPE() const { return "MultiplyModule"; }
