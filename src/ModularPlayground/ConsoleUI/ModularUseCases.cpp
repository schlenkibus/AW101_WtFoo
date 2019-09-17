#include "ModularUseCases.h"
#include "../../DSPNodes/DSPClock.h"
#include "../../DSPNodes/DSPCollection.h"
#include <string>

bool ModularUseCases::handleCommand(const std::string &command) {

  if (command == "show") {
    std::cout << *m_app.getRootNode() << std::endl;
    return true;
  } else if (command == "add") {
    return handleAdd();
  } else if (command == "set_signal") {
    return handleSetSignal();
  } else if (command == "connect") {
      return handleConnect();
  } else if (command == "remove") {
    return handleRemove();
  } else if (command == "disconnect") {
    return handleDisconnect();
  }

  return false;
}

ModularUseCases::ModularUseCases(ModularPlaygroundApplication &app)
    : m_app{app} {}

std::string promptUser(const std::string &text) {
  std::string _ret;
  std::cout << text;
  std::cin >> _ret;
  return _ret;
}

bool ModularUseCases::handleAdd() {

  DSPNode *node = nullptr;
  try {
    node = m_app.getNode(LibUUID::UUID(promptUser("Parent UUID: ")));
  } catch (...) {
    std::cerr << "invalid uuid!";
    return false;
  }

  if (auto container = dynamic_cast<DSPContainer*>(node)) {
    std::cout << "available nodes:\n";

    for (auto &nodeDesc : {"clock", "container", "collection"})
      std::cout << nodeDesc << '\n';

    auto type = promptUser("what kind of node?");

    if (type == "clock") {
      auto length = std::stoi(promptUser("ticks per cycle"));
      std::cout << "created: " << *container->createNode<DSPClock>(length);
      return true;
    } else if (type == "container") {
      std::cout << "created: " << *container->createNode<DSPContainer>();
      return true;
    } else if (type == "collection") {
      std::cout << "created: " << *container->createNode<DSPCollection>();
      return true;
    }
  }
  std::cerr << "did not create new DSPNode!" << std::endl;
  return false;
}

bool ModularUseCases::handleConnect() {
  DSPNode *srcNode = nullptr;
  try {
    srcNode = m_app.getNode(LibUUID::UUID(promptUser("uuid of source:")));
  } catch (...) {
    std::cerr << "could not fetch source node!\n";
    return false;
  }

  if (srcNode == nullptr) {
    std::cerr << "could not find source node!\n";
    return false;
  }

  DSPNode *targetNode = nullptr;

  try {
    targetNode = m_app.getNode(LibUUID::UUID(promptUser("uuid of target:")));
  } catch (...) {
    std::cerr << "could not find target node!\n";
    return false;
  }

  if (auto mixer = dynamic_cast<DSPInput *>(targetNode)) {
    mixer->connect(srcNode);
    std::cout << "successfully connected source: " << *srcNode
              << " to target: " << *targetNode << std::endl;
    return true;
  }

  return false;
}

bool ModularUseCases::handleRemove() {
  DSPNode *targetNode = nullptr;

  try {
    targetNode = m_app.getNode(
        LibUUID::UUID(promptUser("uuid of container to remove from:")));
  } catch (...) {
    std::cerr << "could not find container node!\n";
    return false;
  }

  DSPNode *srcNode = nullptr;
  try {
    srcNode = m_app.getNode(LibUUID::UUID(promptUser("uuid to deleted node:")));
  } catch (...) {
    std::cerr << "could not fetch node!\n";
    return false;
  }

  if (srcNode == nullptr) {
    std::cerr << "could not find source node!\n";
    return false;
  }

  if (auto container = dynamic_cast<DSPContainer *>(targetNode)) {
    container->removeNode(srcNode->m_uuid);
    std::cout << "successfully removed node from container: " << *targetNode
              << std::endl;
    return true;
  }

  return false;
}

bool ModularUseCases::handleDisconnect() {
  DSPNode *srcNode = nullptr;
  try {
    srcNode = m_app.getNode(
        LibUUID::UUID(promptUser("uuid of source to disconnect:")));
  } catch (...) {
    std::cerr << "could not fetch source node!\n";
    return false;
  }

  if (srcNode == nullptr) {
    std::cerr << "could not find source node!\n";
    return false;
  }

  DSPNode *targetNode = nullptr;

  try {
    targetNode = m_app.getNode(
        LibUUID::UUID(promptUser("uuid of target to disconnect from:")));
  } catch (...) {
    std::cerr << "could not find target node!\n";
    return false;
  }

  if (auto input = dynamic_cast<DSPInput *>(targetNode)) {
    input->remove(srcNode);
    std::cout << "successfully disconnected source: " << *srcNode
              << " from target: " << *targetNode << std::endl;
    return true;
  }

  return false;
}

bool ModularUseCases::handleSetSignal() {
  try {
    auto id = LibUUID::UUID{promptUser("UUID Of Node to set:")};
    auto node = m_app.getNode(id);
    auto signal = std::stod(promptUser("signal in range: [-1.0, 1.0]:"));
    node->signal = signal;
    std::cout << *node << std::endl;
    return true;
  } catch(...) {
    std::cerr << "could not set signal!" << std::endl;
    return false;
  }
}
