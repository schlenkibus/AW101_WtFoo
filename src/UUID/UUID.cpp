#include "UUID.h"

namespace LibUUID {

    UUID::UUID() {
      uuid_generate_random(m_uuid);
      char uuid_buffer[37];
      uuid_unparse_lower(m_uuid, uuid_buffer);
      m_string = uuid_buffer;
    }

    UUID::UUID(const std::string &uuid) {
        uuid_parse(uuid.data(), m_uuid);
        m_string = uuid;
    }

    std::ostream &operator<<(std::ostream &stream, const LibUUID::UUID &uuid) {
      return stream << uuid.m_string;
    }
    }