#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <iostream>
#include <string>

#define TEST(function, name) \
if (function()) { \
    std::cout << name << " success\n"; \
} else { \
    std::cout << name << " failure\n"; \
    result = false; \
}

#endif