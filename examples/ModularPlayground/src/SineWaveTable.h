#pragma once
#include <array>
#include <libDSP/include/DSPInfo.h>
#include <math.h>
#include <vector>

template <size_t size>
class SineWaveTable {
public:
    SineWaveTable() {
        auto phaseInc = 1 * M_2_PI / DSPInfo::SampleRate;

        for(int i=0;i<=size;i++)
        {
            constexpr double rads = M_PI/180.0;
            constexpr double step = 360.0 / size;
            m_data[i] = 0.5 * std::sin(step*i*rads);
        }
    }

    inline constexpr const int getSize() const { return size; }
    inline const float get(int i) const { if(i < size) return m_data[i]; return 0;}
protected:
    std::array<float, size> m_data;
};