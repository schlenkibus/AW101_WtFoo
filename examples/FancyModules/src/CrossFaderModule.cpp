#include "CrossFaderModule.h"

CrossFaderModule::CrossFaderModule(DSPHost *host) : DSPModule(host) {
  mix = createParameter("Mix", 0, 0.0, 1.0, 4);
  createInput("1");
  r = createInput("2");
  l = findInput("1");
  o = createOutput("~");
}

void CrossFaderModule::tick() {
  DSPContainer::tick();

  auto lFac = 1.0 - mix->getValue();
  auto t1 = l->getSignal() * lFac;
  auto t2 = r->getSignal() * mix->getValue();

  o->set((t1 * 0.5) + (t2 * 0.5));
}

