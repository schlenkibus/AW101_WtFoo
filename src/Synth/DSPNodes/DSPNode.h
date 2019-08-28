#pragma once

class DSPNode {
public:
    virtual void tick() = 0;
    virtual void reset();
    float signal{0};
};
