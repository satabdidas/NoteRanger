#ifndef __COMMON_MACROS_H__
#define __COMMON_MACROS_H__

#include <cassert>
#include <iostream>

#define notesAssert(cond, str) \
    if (!cond) { std::cerr << str << "\n"; assert(cond); }

#endif // __COMMON_MACROS_H__
