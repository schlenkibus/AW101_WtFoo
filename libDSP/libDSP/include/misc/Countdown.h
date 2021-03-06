#pragma once
#include <algorithm>

template<typename T>
class Countdown {
public:
    explicit Countdown(T l) : length{l}, current{0} {}

    void setLength(T l) {
        length = l;
    }

    bool tick_check() {
        current++;
        return length >= current;
    }

    void reset() {
        current = 0;
    }

    float getPercentage() const {
        return length / std::max<T>(current, 1);
    }

  private:
    T length;
    T current;
};
