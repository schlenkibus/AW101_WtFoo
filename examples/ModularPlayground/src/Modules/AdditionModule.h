#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class AdditionModule : public DSPModule {
public:
    explicit AdditionModule(DSPHost* host);
    void tick() override;

  private:
    Output* m_out;
    Input* m_inI;
    Input* m_inII;
};
