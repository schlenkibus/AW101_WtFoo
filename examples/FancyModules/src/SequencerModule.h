#pragma once

#include <libDSP/include/Modules/DSPModule.h>

class SequencerModule : public DSPModule {
public:
    explicit SequencerModule(DSPHost *parent);
    void tickInternals() override;
    private:
    size_t m_currentIndex{0};
    bool stepped = false;
    std::array<Parameter*, 8> m_stepValues{nullptr};
    DSPInputNode* m_input;
    DSPOutputNode* m_output;
};