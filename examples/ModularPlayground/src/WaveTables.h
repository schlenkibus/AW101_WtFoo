#pragma once
#include <array>
#include <libDSP/include/DSPInfo.h>
#include <math.h>
#include <vector>

template <size_t size> class WaveTable {
public:
  inline constexpr const int getSize() const { return size; };
  inline const float get(int i) const {
    if (i < size)
      return m_data[i];
    return 0;
  };

protected:
  std::array<float, size> m_data;
};

template <size_t size> class SineWaveTable : public WaveTable<size> {
public:
  SineWaveTable() : WaveTable<size>() {
    auto phaseInc = 1 * M_2_PI / DSPInfo::SampleRate;

    for (int i = 0; i <= size; i++) {
      constexpr double rads = M_PI / 180.0;
      constexpr double step = 360.0 / size;
      WaveTable<size>::m_data[i] = 0.5 * std::sin(step * i * rads);
    }
  }
};

template <size_t size> class SawWaveTable : public WaveTable<size> {
public:
  SawWaveTable() {
    auto phaseInc = 2.0 / size;

    WaveTable<size>::m_data[0] = -1.0;
    for (int i = 1; i <= size; i++) {
      WaveTable<size>::m_data[i] = WaveTable<size>::m_data[i - 1] + phaseInc;
    }
  }
};

template <size_t size> class TriangleWaveTable : public WaveTable<size> {
public:
    TriangleWaveTable() {
        auto phaseInc = 2.0 / size;

        WaveTable<size>::m_data[0] = -1.0;
        for (int i = 1; i <= size; i++) {
            if(i < size / 2)
                WaveTable<size>::m_data[i] = WaveTable<size>::m_data[i - 1] + phaseInc;
            else
                WaveTable<size>::m_data[i] = WaveTable<size>::m_data[i - 1] - phaseInc;
        }
    }
};