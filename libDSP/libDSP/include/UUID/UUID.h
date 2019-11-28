#pragma once
#include <iostream>
#include <string>
#include <uuid/uuid.h>

namespace LibUUID
{
  class UUID
  {
   public:
    UUID();
    explicit UUID(const std::string &uuid);
    uuid_t m_uuid {};
    std::string m_string {};

    friend std::ostream &operator<<(std::ostream &stream, const LibUUID::UUID &matrix);
    friend const bool operator==(const LibUUID::UUID &lhs, const LibUUID::UUID &rhs)
    {
      return uuid_compare(lhs.m_uuid, rhs.m_uuid) == 0;
    }

    friend const bool operator!=(const LibUUID::UUID &lhs, const LibUUID::UUID &rhs)
    {
      return uuid_compare(lhs.m_uuid, rhs.m_uuid) != 0;
    }
  };

}