#include "libDSP/include/DSPNodes/DSPContainer.h"
#include <algorithm>

void DSPContainer::removeNode(const LibUUID::UUID &uuid) {
  try {
    m_nodes.erase(
        std::remove_if(m_nodes.begin(), m_nodes.end(),
                       [uuid](auto &node) { return node->m_uuid == uuid; }),
        m_nodes.end());
  } catch (...) {
    std::cerr << "could not removeIngoingConnection DSPNode: " << uuid
              << " from Container: " << m_uuid << std::endl;
  }
}

void DSPContainer::tick() {
  for (auto &node : m_nodes) {
    node->tick();
  }
}

void DSPContainer::collectNodes(std::vector<DSPNode *> &vector) {
  for (auto &node : m_nodes) {
    if (const auto container = dynamic_cast<DSPContainer *>(node.get())) {
      container->collectNodes(vector);
    }
    vector.emplace_back(&*node);
  }
}

std::vector<DSPNode *> DSPContainer::getChildren() {
  std::vector<DSPNode *> ret;
  for (auto &c : m_nodes) {
    ret.emplace_back(c.get());
  }
  return ret;
}
