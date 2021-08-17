#pragma once

#include <splat/symbol_export.h>

#if SERVER_SHARED
#   if BUILDING_SERVER
#       define SERVER_API SYMBOL_EXPORT
#   else
#       define SERVER_API SYMBOL_IMPORT
#   endif
#else
#   define SERVER_API
#endif
