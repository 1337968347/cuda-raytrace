#include "pbrt.h"

#if defined(PBRT_IS_WINDOWS)
typedef volatile LONG AtomicInt32;

#endif