#include "SineWaveTable.h"

SineWaveTable::SineWaveTable(size_t size) : m_size{size} {
    m_data.reserve(m_size);

    for(int i=0;i<=size;i++)
    {
      double rads = M_PI/180.0;
      double step = 360.0 / size;
      m_data[i] = 0.5 * std::sin(step*i*rads);
    }
}
