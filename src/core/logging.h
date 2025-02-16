#include <iostream>

#if defined(MAPS_DEBUG)
#define LOG_DEBUG(x) std::cout << x << "\n"
#else
#define LOG_DEBUG(x)
#endif