#pragma once

#include <libDSP/include/Modules/DSPModule.h>

class SequencerModule : public DSPModule {
public:
    explicit SequencerModule(DSPHost *parent);
    void tick() override;
    private:
    size_t m_currentIndex;
    bool stepped = false;
    std::array<Parameter*, 8> m_stepValues{nullptr};
    Input* m_input;
    Output* m_output;
};