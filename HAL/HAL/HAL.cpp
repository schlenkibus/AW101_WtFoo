#include "HAL.h"

HAL::HAL(DSPHost *host)
    : m_host { host }
{
  m_hall.onDeviceHello([this](auto message) {
    if(isHelloMessage(message))
    {
      handleHello(message);
    }
    else
    {
      handleNormalMessage(message);
    }
  });
}

std::string findKey(const std::string &key, const std::string &message)
{
  auto it = message.find(key + '{');
  if(it != message.size())
  {
    auto until = message.find('}', it) - 1;
    if(until != message.size())
    {
      auto from = it + key.size() + 1;
      return message.substr(from, until - from + 1);
    }
  }
  return "";
}

void HAL::handleHello(const std::string &helloMessage)
{
  auto type = findKey("TYPE", helloMessage);
  try
  {
    auto &cb = m_hardwareFactories[type];
    m_hardwareObjects.emplace_back(std::move(cb(helloMessage, m_host)));
  }
  catch(const std::runtime_error &e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch(...)
  {
    std::cerr << "unokwn error occured!" << std::endl;
  }
}

bool HAL::isHelloMessage(const std::string &message) const
{
  return message.find("HELLO") == 0;
}

void HAL::handleNormalMessage(const std::string &message)
{
  std::cout << message << std::endl;
}

void HAL::registerHardware(const std::string &name, const HAL::tCreateHardwareCB &cb)
{
  m_hardwareFactories[name] = cb;
}