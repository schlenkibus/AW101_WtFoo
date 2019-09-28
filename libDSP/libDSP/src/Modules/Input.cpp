#include "libDSP/include/Modules/Input.h"
#include "libDSP/include/Modules/Output.h"

void Input::connect(Output *o) {
  if (node && o) {
    node->connect(o->node);
    m_connectedTo = o;
  }
}

void Input::tryDisconnect(Output *o) {
    if(node && o &&node->connectedTo() == o->node)
      node->removeIngoingConnection();
}

Output *Input::connectedTo() {
  return m_connectedTo;
}

float Input::getSignal() const { if(node) return node->signal; return 0.0; }

void Input::tick(){
    node->tick();
}

const LibUUID::UUID& Input::getUUID() const{
    return node->m_uuid;
}