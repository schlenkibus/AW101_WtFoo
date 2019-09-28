#pragma once
#include "DSPNode.h"
#include <memory>
#include <vector>

class DSPContainer : public DSPNode {
public:
  void tick() override;
  template <class Node, typename... tArgs> Node *createNode(tArgs... args) {
    m_nodes.emplace_back(std::make_unique<Node>(args...));
    return dynamic_cast<Node *>(m_nodes.back().get());
  }

  virtual void removeNode(const LibUUID::UUID &);
  void collectNodes(std::vector<DSPNode *> &vector);

  std::vector<DSPNode *> getChildren();

private:
  std::vector<std::unique_ptr<DSPNode>> m_nodes;
};
