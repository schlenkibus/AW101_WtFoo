#pragma once
#include <array>
#include <vector>
#include <cstddef>
#include <mutex>


template<class T, size_t size>
class RingBuffer {
public:
    RingBuffer() : m_data{} {
    }

    virtual void put(T t) {
        m_data[m_head] = t;
        m_head++;
        if(m_head >= size)
          m_head=0;
    }

  T* getDataBeginPtr() {
      return m_data.data();
  }

  T* getDataEndPtr() {
      return m_data.data() + (sizeof(T) * m_data.size());
  }

  constexpr size_t getSize() const {
        return size;
    }

protected:
    size_t m_head = 0;
    std::array<T, size> m_data;
};


template <class T, size_t size, size_t nThPut>
class NthRingBuffer : public RingBuffer<T, size> {
    public:
        void put(T t) override
        {
            nthTry++;
            if(nthTry == nThPut)
            {
              nthTry = 0;
              RingBuffer<T,size>::put(t);
            }
        }
protected:
  size_t nthTry{0};
};