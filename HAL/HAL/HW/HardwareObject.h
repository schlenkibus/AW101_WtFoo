#pragma once

class HALObject;

class HardwareObject {
public:
  explicit HardwareObject(HALObject *parent);

private:
  HALObject *m_parent;
};
