#pragma once


class Frame {
public:
    Frame();
    explicit Frame(unsigned long frame);
    float l{0.0};
    float r{0.0};
    unsigned long numFrame;
};