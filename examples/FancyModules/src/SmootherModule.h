#pragma once

#include <libDSP/include/Modules/DSPModule.h>

class SmootherModule : public DSPModule {
public:
    void tick() override;

    explicit SmootherModule(DSPHost *parent);

    const char *getName() override;
private:
    float m_lastSignal = 0;
    Input* m_input;
    Output* m_output;
    Parameter* m_smoothingFactor;
};


