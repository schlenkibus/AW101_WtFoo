#include "../../include/Modules/Output.h"

Output::Output(DSPModule* parent, std::string na, DSPOutputNode* no)
    : name{std::move(na)}, node{no} {}

DSPModule * Output::getModule(){
    return nullptr;
}