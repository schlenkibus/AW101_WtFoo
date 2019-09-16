#include "DSPNode.h"
#include <iostream>

void DSPNode::reset(){
    signal = 0;
}

DSPNode::DSPNode() : m_uuid{} {
  std::cout << m_uuid << std::endl;
}
