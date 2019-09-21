#include "ModularUseCases.h"
#include <string>

bool ModularUseCases::handleCommand(const std::string &command) {
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