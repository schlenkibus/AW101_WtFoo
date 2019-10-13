#pragma once
#include <client_ws.hpp>
#include <vector>
#include <memory>
#include <HAL/HAL.h>
#include "HAL/HW/HardwareObject.h"

class IODevice : public HardwareObject
{
 public:
  explicit IODevice(const std::string& hello, DSPHost* host);
  const char* TYPE() override;
  DSPModule* createModule() override;

 private:
  float m_in;
  float m_out;
  std::vector<std::unique_ptr<SimpleWeb::SocketClient<SimpleWeb::WS>>> m_inputs;
  std::vector<std::unique_ptr<SimpleWeb::SocketClient<SimpleWeb::WS>>> m_outputs;
};
