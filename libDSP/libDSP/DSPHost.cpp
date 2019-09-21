#include "DSPHost.h"

DSPHost::DSPHost() {}

void DSPHost::tick() {}

void DSPHost::onRemoveOutput(Output &o) {
  for(auto& module: m_modules) {
    for(auto& i: module->getInputs()) {
      i->tryDisconnect(o);
    }
  }
}
