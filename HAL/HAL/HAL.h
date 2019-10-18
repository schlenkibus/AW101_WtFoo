#pragma once
#include <HAL/hall/WelcomeHall.h>
#include <libDSP/include/DSPHost.h>
#include "HW/HardwareObject.h"

class HAL {
 public:
  using tCreateHardwareCB = std::function<std::unique_ptr<HardwareObject>(const std::string&, DSPHost* host)>;
  explicit HAL(DSPHost *host);

  void registerHardware(const std::string& name, const tCreateHardwareCB& cb);
  template<typename tCB>
  void registerMessageHandler(const tCB& cb) {
    m_messageCallbacks.emplace_back(cb);
  }

 private:
  WelcomeHall m_hall;
  DSPHost *m_host;

  std::unordered_map<std::string, tCreateHardwareCB> m_hardwareFactories{};
  std::unordered_map<std::string, std::unique_ptr<HardwareObject>> m_hardwareObjects;

  bool isHelloMessage(const std::string& message) const;
  void handleHello(const std::string& helloMessage);
  void handleNormalMessage(const std::string& message);

  std::vector<std::function<bool(const std::string message)>>  m_messageCallbacks;
};