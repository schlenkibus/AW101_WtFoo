#pragma once
#include "libDSP/include/DSPNodes/DSPInputNode.h"

class Output;

class Input {
public:
    Input(std::string na, DSPInputNode *no) : name{std::move(na)}, node{no} {}
    std::string name;

    friend bool operator==(const Input &lhs,
                           const Input &rhs) {
        return lhs.name == rhs.name;
    }

    float getSignal() const;

    void connect(Output& o);
    void tryDisconnect(Output& o);
    void tick();
private:
    DSPInputNode *node;

    friend class DSPModule;
    friend class Output;
};
