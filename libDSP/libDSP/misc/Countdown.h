#pragma once

template<typename T>
class Countdown {
public:
    explicit Countdown(T l) : length{l}, current{0} {}

    bool tick_check() {
        current++;
        return length >= current;
    }

  private:
    const T length;
    T current;
};
