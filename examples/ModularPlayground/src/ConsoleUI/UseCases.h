#pragma once
#include <string>

class UseCases {
public:
    virtual bool handleCommand(const std::string& command) = 0;
};

