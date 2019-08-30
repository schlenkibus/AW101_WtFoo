#pragma once

using DSPSignalIndex = int;

namespace DSPInfo {
    constexpr static int SampleRate = 44100;
    constexpr static int SimulationSteps = 200;

    namespace Envelope {
        static int TransitionTime = DSPInfo::SampleRate / 5;
        static float Exciter = 0.0;
    }
};