#pragma once
#include <cstdio>

// Usage: QS_LOG("physics", "y = %f", y);
#define QS_LOG(channel, ...)                    \
  do {                                          \
    std::printf("[" channel "] ");              \
    std::printf(__VA_ARGS__);                   \
    std::printf("\n");                          \
  } while (0)
