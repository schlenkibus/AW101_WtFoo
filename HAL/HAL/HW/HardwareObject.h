#pragma once
#include "HardwareInput.h"
#include "HardwareOutput.h"
#include <memory>
#include <string>
#include <vector>

class HardwareObject {
public:
  explicit HardwareObject(const std::string &uuid, const std::string &inputs,
                          const std::string &outputs);

private:
    const std::string m_uuid;
    std::vector<std::unique_ptr<HardwareInput>> m_inputs;
    std::vector<std::unique_ptr<HardwareOutput>> m_outputs;
};
