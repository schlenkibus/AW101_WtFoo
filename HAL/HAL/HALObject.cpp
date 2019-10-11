#include "HALObject.h"

HALObject::HALObject(DSPHost *host) : m_host{host} {
    m_hall.onDeviceHello([this](auto message) {
        if(isHelloMessage(message)) {
            handleHello(message);
        } else {
            handleNormalMessage(message);
        }
    });
}

std::string findKey(const std::string& key, const std::string& message) {
    auto it = message.find(key + '{');
    if(it != message.size())
    {
        auto until = message.rfind('}');
        if(until == message.size() - 1)
        {
            return message.substr(it + key.size() + 1, until);
        }
    }
    return "";
}

void HALObject::handleHello(const std::string &helloMessage) {
    auto uuid = findKey("UUID", helloMessage);
    auto type = findKey("TYPE", helloMessage);
    auto inputs = findKey("INPUTS", helloMessage);
    auto outputs = findKey("OUTPUTS", helloMessage);
}
bool HALObject::isHelloMessage(const std::string &message) const {
  return message.find("HELLO") == 0;
}

void HALObject::handleNormalMessage(const std::string &message) {
  auto uuid = findKey("UUID", message);

}
