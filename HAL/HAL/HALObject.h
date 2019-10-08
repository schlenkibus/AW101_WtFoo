#pragma once
#include <libDSP/include/DSPHost.h>

class HardwareObject;

class HALObject {
public:
  explicit HALObject(DSPHost *host);


  //TODO add register hardware object and implement callbacks to modules ->
  // create modules inside this registerModules -> from inside the plugins
private:
  DSPHost *m_host;

  std::map<std::string, std::function<HardwareObject *(HALObject *)>>
      m_hardwareFactories;
};
