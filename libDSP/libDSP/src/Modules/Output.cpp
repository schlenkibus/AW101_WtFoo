#include "../../include/Modules/Output.h"
#include "libDSP/include/Modules/DSPModule.h"
#include "libDSP/include/DSPHost.h"

Output::Output(DSPModule* parent, std::string na, DSPOutputNode* no)
    : name{std::move(na)}, node{no}, parent{parent} {}

DSPModule * Output::getModule(){
    return parent;
}

Output::~Output()
{
  parent->getHost()->onRemoveOutput(this);
}
