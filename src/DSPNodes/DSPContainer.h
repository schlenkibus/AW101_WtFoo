#pragma once
#include "DSPMixerNode.h"
#include "DSPNode.h"
#include <memory>
#include <vector>

class DSPContainer : public DSPNode {
public:
  explicit DSPContainer();

  void tick() override;

  template <class Node, typename... tArgs> DSPNode* createNode(tArgs... args) {
    auto& ret = m_nodes.emplace_back(std::make_unique<Node>(args...));
    return ret.get();
  }

  void removeNode(const LibUUID::UUID &);
  void collectNodes(std::vector<DSPNode *>& vector);

  const char* TYPE() const override { return "CONTAINER"; }

  friend std::ostream&operator<<(std::ostream& stream, DSPContainer* container) {
    return stream << (DSPContainer&)*container;
  }

  friend std::ostream& operator<<(std::ostream& stream, const DSPContainer& node) {
    stream << *((const DSPNode*)&node) << " Children:\n";
    for(auto& child: node.m_nodes) {
      stream << "\t" << *child << "\n";
    }
    return stream;
  }
private:
  std::vector<std::unique_ptr<DSPNode>> m_nodes;
  DSPMixerNode m_outputmixer;
};
