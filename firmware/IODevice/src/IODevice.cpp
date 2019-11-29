#include <libDSP/include/Modules/DSPModule.h>
#include "IODevice.h"

std::string findKey(const std::string &key, const std::string &message)
{
  auto it = message.find(key + '{');
  if(it != message.size())
  {
    auto until = message.find('}', it);
    if(until == message.size() - 1)
    {
      return message.substr(it + key.size() + 1, until);
    }
  }
  return "";
}

class IOModule : public DSPModule
{
 public:
  IOModule(DSPHost *parent, int inputs, IODevice *dev)
      : DSPModule(parent)
  {
    for(auto i = 0; i < inputs; i++)
      createOutput(std::to_string(i));
  }

  const char *getName() override
  {
    return "IODevice";
  }

  void set(int index, float d)
  {
    getOutputs()[index]->set(d);
  }
};

IODevice::IODevice(const std::string &hello, DSPHost *host, HAL *hal)
    : HardwareObject(hello, host)
{
  auto ip = findKey("IP", hello);
  auto inputs = findKey("INPUTS", hello);
  std::vector<int> ids;

  std::stringstream ss(inputs);

  for(int i; ss >> i;)
  {
    ids.push_back(i);
    if(ss.peek() == ',')
      ss.ignore();
  }

  hal->registerMessageHandler([this, ip](auto message) {
    auto str = message;
    auto cIP = findKey("IP", str);
    if(ip == cIP)
    {
      auto id = std::stoi(findKey("ID", str));
      auto val = findKey("VALUE", str);

      if(m_module)
      {
        m_module->set(id, std::stoi(val) / 1023.0);
      }
      return true;
    }
    return false;
  });

  m_module = dynamic_cast<IOModule *>(host->createRootModule(std::make_unique<IOModule>(host, ids.size(), this)));
}

IODevice::~IODevice()
{
}

const char *IODevice::TYPE()
{
  return "IO";
}

DSPModule *IODevice::createModule()
{

  return nullptr;
}
