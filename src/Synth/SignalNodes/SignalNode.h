#pragma once


class SignalNode {
public:
    virtual void tick() = 0;
    bool signal;
};
