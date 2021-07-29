#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <iostream>
#include <string>

#define TEST(function, name) \
if (function()) { \
    std::cout << "\t" << name << " success\n"; \
} else { \
    std::cout << "\t" << name << " failure\n"; \
    result = false; \
}

#endif
