#include "StreamUI.h"

StreamUI::StreamUI(std::istream &stream) : m_stream{stream} {
}

int StreamUI::run() {
  running = true;
  std::string command{};
  while(m_stream >> command) {
    auto uiResult = handleUIUseCase(command);
    if (uiResult == static_cast<int>(UseCaseReturnValues::HANDLED_SUCCESS))
      break;
    else if (uiResult != static_cast<int>(UseCaseReturnValues::UNHANDLED))
      return uiResult;

    bool successful = false;
    for(auto& usecase: m_useCases) {
      if(usecase->handleCommand(command)) {
          successful = true;
          break;
      }
    }

    if(!successful) {
        std::cerr << "unhandled command: " << command << std::endl;
    }
  }

  return 0;
}

int StreamUI::handleUIUseCase(const std::string &basicString) {
  if(basicString == "exit")
    return static_cast<int>(UseCaseReturnValues::HANDLED_ERROR);

  return static_cast<int>(UseCaseReturnValues::UNHANDLED);
}
void StreamUI::addUseCases(UseCases *cases) {
  m_useCases.emplace_back(cases);
}
