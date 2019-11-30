#include "Connection.h"

Connection::Connection(const DSPOutputNode *from, const DSPInputNode *to) : m_from{from}, m_to{to} {}
