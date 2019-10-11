#pragma once
#include <HAL/hall/WelcomeHall.h>
#include <libDSP/include/DSPHost.h>

class HardwareObject;

class HALObject {
public:
  explicit HALObject(DSPHost *host);

  // TODO add register hardware object and implement callbacks to modules ->
  // create modules inside this registerModules -> from inside the plugins
private:
  WelcomeHall m_hall;
  DSPHost *m_host;

  std::map<std::string, DSPHardwareModule*> m_instantiatedModules();
  std::vector<HardwareObject> m_hardwareObjects;

  bool isHelloMessage(const std::string& message) const;
  void handleHello(const std::string& helloMessage);
  void handleNormalMessage(const std::string& message);
};
