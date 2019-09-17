#include "DSPCollection.h"

void DSPCollection::tick() {
  for(auto& node: m_nodes) {
    node->tick();
  }
  signal = 0;
}

const char *DSPCollection::TYPE() const { return "COLLECTION"; }
