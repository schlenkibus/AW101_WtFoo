#pragma once
#include <functional>

template<typename tRet, typename tArg>
class Signal {
public:
    using tCB = std::function<tRet(tArg)>;
    Signal() {

    }
protected:

};
