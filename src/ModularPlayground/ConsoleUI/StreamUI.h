#pragma once

#include "ModularUseCases.h"
#include <istream>
class StreamUI {
public:
  explicit StreamUI(std::istream &stream);
  int run();
  void addUseCases(UseCases *cases);
private:
  enum class UseCaseReturnValues : int {
    UNHANDLED,
    HANDLED_SUCCESS,
    HANDLED_ERROR
  };
  std::vector<UseCases*> m_useCases;
  std::istream &m_stream;
  int handleUIUseCase(const std::string &basicString);

  bool running = false;
};