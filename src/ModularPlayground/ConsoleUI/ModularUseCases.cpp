#include "ModularUseCases.h"
#include "../../DSPNodes/DSPClock.h"
#include <string>

bool ModularUseCases::handleCommand(const std::string &command) {

  if(command == "show") {
    for(auto& node: m_app.collectNodes()) {
        std::cout << *node << std::endl;
    }
    return true;
  } else if(command == "add") {
    std::string input{};
    std::cout << "parent uuid: ";
    std::cin >> input;

    DSPNode* node = nullptr;

    try {
      node = m_app.getNode(LibUUID::UUID{input});
    } catch (...) {
      std::cerr << "invalid uuid!!!\n";
      return true;
    }

    if(auto container = dynamic_cast<DSPContainer*>(node)) {
      std::cout << "what kind of container?" << std::endl;
      std::cin >> input;
      if(input == "clock") {
        std::cout << "ticklenght: ";
        std::cin >> input;
        int ticks = std::stoi(input);
        std::cout << "created: " << *container->createNode<DSPClock>(ticks);
        return true;
      }
    }
  }

  return false;
}

ModularUseCases::ModularUseCases(ModularPlaygroundApplication &app) : m_app{app} {

}
