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


const Output * Input::connectedTo() const {
  return m_connectedTo;
}

float Input::getSignal() const { if(node) return node->signal; return 0.0; }

void Input::tick(){
    node->tick();
}