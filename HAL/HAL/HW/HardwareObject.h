#pragma once
#include "HardwareInput.h"
#include "HardwareOutput.h"
#include <memory>
#include <string>
#include <vector>

class DSPHost;
class DSPModule;

class HardwareObject
{
 public:
  explicit HardwareObject(const std::string& hello, DSPHost* host);
  virtual DSPModule* createModule() = 0;
  virtual const char* TYPE() = 0;

 private:
  DSPHost* m_host { nullptr };
};
