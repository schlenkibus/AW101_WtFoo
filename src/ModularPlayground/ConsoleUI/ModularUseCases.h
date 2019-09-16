#pragma once

#include "../../misc/UseCases.h"
#include "../ModularPlaygroundApplication.h"

class ModularUseCases : public UseCases {
public:
  explicit ModularUseCases(ModularPlaygroundApplication& app);
  bool handleCommand(const std::string& command) override;

private:
  bool handleAdd();
  ModularPlaygroundApplication& m_app;
  bool handleConnect();
};


