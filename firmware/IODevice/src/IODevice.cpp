#include <libDSP/include/Modules/DSPModule.h>
#include "IODevice.h"

std::string findKey(const std::string &key, const std::string &message) {
    auto it = message.find(key + '{');
    if (it != message.size()) {
        auto until = message.find('}', it);
        if (until == message.size() - 1) {
            return message.substr(it + key.size() + 1, until);
        }
    }
    return "";
}

class IOModule : public DSPModule {
public:
    IOModule(DSPHost *parent, IODevice *dev)
            : DSPModule(parent) {
        m_button = createOutput("Button 0");
        m_button2 = createOutput("Button 1 ");
    }

    Output *getButton0() {
        return m_button;
    }

    Output *getButton1() {
        return m_button2;
    }

    const char *getName() override {
        return "IODevice";
    }

private:
    Output *m_button{nullptr};
    Output *m_button2{nullptr};
};

IODevice::IODevice(const std::string &hello, DSPHost *host)
        : HardwareObject(hello, host) {
    auto ip = findKey("IP", hello);
    for (auto &inPut: {"INPUT0", "INPUT1"}) {
        auto in = findKey("PORT", findKey(inPut, hello));
        const auto is0 = strcmp(inPut, "INPUT0") == 0;
        m_inputs.emplace_back(std::make_unique<IODevice::Input>(ip, std::stoi(in), [this, is0](auto c, auto message) {
            auto str = message->string();
            std::cout << str << std::endl;
            m_in = std::stoi(str) / 1023;
            if (m_module) {
                if (is0)
                    m_module->getButton0()->set(m_in);
                else
                    m_module->getButton1()->set(m_in);
            }
        }));
    }


    m_module = static_cast<IOModule *>(host->createModule(std::make_unique<IOModule>(host, this)));
}

IODevice::~IODevice() {
    m_inputs.clear();
}

const char *IODevice::TYPE() {
    return "IO";
}

DSPModule *IODevice::createModule() {

    return nullptr;
}
