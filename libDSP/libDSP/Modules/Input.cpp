#include "Input.h"
#include "Output.h"

void Input::connect(Output &o) {
  if (node)
    node->connect(o.node);
}

void Input::tryDisconnect(Output& o) {
    if(node && node->connectedTo() == o.node)
      node->removeIngoingConnection();
}


float Input::getSignal() const { if(node) return node->signal; return 0.0; }

void Input::tick(){

    node->tick();
}