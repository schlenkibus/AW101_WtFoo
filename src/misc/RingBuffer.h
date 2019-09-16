#pragma once
#include <cstddef>
#include <array>

template<class tData, size_t size>
class RingBuffer {
protected:
    std::array<tData, size> m_data{};
public:
    using tIteratorType = typename decltype(m_data)::size_type;

    explicit RingBuffer(tData def) {
        m_data.fill(def);
        m_writeHead = size / 2;
    }

    void put(const tData& data) {
        m_data[m_writeHead] = data;
        if(m_writeHead == size)
            m_writeHead = 0;
    }

    const std::array<tData, size>& getData() const {
        return m_data;
    }

    tIteratorType getWritePos() const {
        return m_writeHead;
    }

protected:
    tIteratorType m_writeHead;
};


