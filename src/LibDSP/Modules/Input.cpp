#include "Input.h"
#include "Output.h"

void Input::connect(Output &o) {
  if (node)
    node->connect(o.node);
}

float Input::getSignal() { return node->signal; }

void Input::tick(){
    node->tick();
}