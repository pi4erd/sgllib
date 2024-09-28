#pragma once

#include <fmt/format.h>

#define LOGLEVEL_DEBUG 4
#define LOGLEVEL_INFO 3
#define LOGLEVEL_WARN 2
#define LOGLEVEL_ERROR 1
#define LOGLEVEL_NONE 0

static int LOG_LEVEL = 0;

void set_log_level(int log_level);

#define LOG_DEBUG(...) if(LOG_LEVEL >= LOGLEVEL_DEBUG) { fmt::println(">\tDEBUG:\t{}", fmt::format(__VA_ARGS__)); }
#define LOG_INFO(...) if(LOG_LEVEL >= LOGLEVEL_INFO) { fmt::println(">>\tINFO:\t{}", fmt::format(__VA_ARGS__)); }
#define LOG_WARN(...) if(LOG_LEVEL >= LOGLEVEL_WARN) { fmt::println(">>>\tWARN:\t{}", fmt::format(__VA_ARGS__)); }
#define LOG_ERROR(...) if(LOG_LEVEL >= LOGLEVEL_ERROR) { fmt::println(">>>>\tERROR:\t{}", fmt::format(__VA_ARGS__)); }

inline void set_log_level(int log_level) {
    LOG_LEVEL = log_level;
}
