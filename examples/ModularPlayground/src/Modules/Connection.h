#pragma once
#include <libDSP/include/Modules/Input.h>
#include <libDSP/include/Modules/Output.h>

class Connection {
public:
    Connection(Output* from, Input* to);
    Output* m_from;
    Input* m_to;
};
