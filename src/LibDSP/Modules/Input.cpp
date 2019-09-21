#include "Input.h"
#include "Output.h"

void Input::connect(Output &o) {
  if (node)
    node->connect(o.node);
}

float Input::getSignal() const { if(node) return node->signal; return 0.0; }

void Input::tick(){

    node->tick();
}