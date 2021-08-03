#pragma once

#include <splat/symbol_export.h>

#if CORE_SHARED
#   if BUILDING_CORE
#       define CORE_API SYMBOL_EXPORT
#   else
#       define CORE_API SYMBOL_IMPORT
#   endif
#else
#   define CORE_API
#endif
