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

IODevice::IODevice(const std::string &hello, DSPHost *host)
    : HardwareObject(hello, host)
{
  auto ip = findKey("IP", hello);
  auto port = std::stoi(findKey("PORT", hello));
  auto inputs = findKey("INPUTS", hello);
  std::vector<int> ids;

  std::stringstream ss(inputs);

  for(int i; ss >> i;)
  {
    ids.push_back(i);
    if(ss.peek() == ',')
      ss.ignore();
  }

  m_inputsClient = std::make_unique<SimpleWeb::SocketClient<SimpleWeb::WS>>(ip, port);
  m_inputsClient->config.timeout_idle = 0;
  m_inputsClient->config.timeout_request = 0;
  m_inputsClient->on_open = [this](auto c) {
    std::cerr << c << std::endl;
  };
  m_inputsClient->on_message = [this](auto c, auto message) {
    auto str = message->string();
    std::stringstream ss(str);

    int id;
    int val;
    ss >> id >> val;

    std::cout << id << " " << val << std::endl;
    m_in = std::stoi(str) / 1023;
    if(m_module)
    {
      m_module->set(id, m_in);
    }
  };

  m_inputThread = std::thread([this]() { m_inputsClient->start(); });

  m_module = dynamic_cast<IOModule *>(host->createModule(std::make_unique<IOModule>(host, ids.size(), this)));
}

IODevice::~IODevice()
{
  m_inputsClient->stop();

  m_inputThread.join();
}

const char *IODevice::TYPE()
{
  return "IO";
}

DSPModule *IODevice::createModule()
{

  return nullptr;
}
