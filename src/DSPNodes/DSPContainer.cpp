#include "DSPContainer.h"
#include <algorithm>

DSPContainer::DSPContainer() {}

void DSPContainer::removeNode(const LibUUID::UUID &uuid) {
  try {
    m_nodes.erase(
        std::remove_if(m_nodes.begin(), m_nodes.end(),
                       [uuid](auto &node) { return node->m_uuid == uuid; }),
        m_nodes.end());
  } catch (...) {
    std::cerr << "could not remove DSPNode: " << uuid
              << " from Container: " << m_uuid << std::endl;
  }
}

void DSPContainer::tick() {
  float temp = 0.0;

  for (auto &node : m_nodes) {
    auto ptr = node.get();
    if(ptr) {
        ptr->tick();
        temp += ptr->signal;
    }
  }

  if (!m_nodes.empty()) {
    signal = temp / m_nodes.size();
  } else {
    signal = 0.0;
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

void DSPContainer::print(std::ostream &stream) const {
  DSPNode::print(stream);

  if (!m_nodes.empty()) {
    stream << "SHOWING " << m_nodes.size() << " CHILDREN:\n";
    for (auto &c : m_nodes) {
      stream << *c;
    }
    stream << "END CHILDREN\n";
  }
}
std::vector<DSPNode *> DSPContainer::getChildren() {
  std::vector<DSPNode *> ret;
  for (auto &c : m_nodes) {
    ret.emplace_back(c.get());
  }
  return ret;
}
