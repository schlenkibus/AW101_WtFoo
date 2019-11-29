#include "MultiplicationModule.h"

MultiplicationModule::MultiplicationModule(DSPHost *parent) : DSPModule(parent) {
  createInput("A");
  createInput("B");
  out = createOutput("AxB");

  a = findInput("A");
  b = findInput("B");
}

void MultiplicationModule::tick() {
  DSPContainer::tick();

  out->set(a->getSignal() * b->getSignal());
}

