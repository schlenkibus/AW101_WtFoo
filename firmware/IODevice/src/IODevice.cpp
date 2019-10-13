#include "IODevice.h"

std::string findKey(const std::string& key, const std::string& message)
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

IODevice::IODevice(const std::string& hello, DSPHost* host)
    : HardwareObject(hello, host)
{
  auto ip = findKey("IP", hello);
  auto in = findKey("PORT", findKey("INPUT", hello));
  m_inputs.emplace_back(std::make_unique<SimpleWeb::SocketClient<SimpleWeb::WS>>(ip, std::stoi(in)));
  auto& r = m_inputs.back();

  r->on_message = [this](auto c, auto message) {
    auto str = message->string();
    std::cout << str << std::endl;
    m_in = std::stoi(str) / 1024;
  };

  r->start();
}

const char* IODevice::TYPE()
{
  return "IO";
}

DSPModule* IODevice::createModule()
{

  return nullptr;
}
