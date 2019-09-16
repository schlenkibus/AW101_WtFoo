#include "DSPContainer.h"
#include <algorithm>

DSPContainer::DSPContainer() {

}

void DSPContainer::removeNode(const LibUUID::UUID &uuid) {
  try {
    m_nodes.erase(
        std::remove_if(m_nodes.begin(), m_nodes.end(),
                       [uuid](auto& node) { return node->m_uuid == uuid; }),
        m_nodes.end());
  } catch (...) {
    std::cerr << "could not remove DSPNode: " << uuid
              << " from Container: " << m_uuid << std::endl;
  }
}

void DSPContainer::tick() {
  m_outputmixer.tick();
  signal = m_outputmixer.signal;
}

void DSPContainer::collectNodes(std::vector<DSPNode *>& vector) {
  for(auto& node: m_nodes) {
    if(const auto container = dynamic_cast<DSPContainer*>(node.get())) {
      container->collectNodes(vector);
    }
    vector.emplace_back(&*node);
  }
  vector.emplace_back(&m_outputmixer);
}
