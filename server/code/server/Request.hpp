#pragma once
#include "API.h"

#include <cstddef>

namespace server
{

// base class for requests to the server
// also servers as a request type registry
class SERVER_API Request {
public:
    using TypeID = size_t;
}

}
