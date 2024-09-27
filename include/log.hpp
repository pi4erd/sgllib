#pragma once

#include <string>
#include <fmt/format.h>

#define LOGLEVEL_DEBUG 4
#define LOGLEVEL_INFO 3
#define LOGLEVEL_WARN 2
#define LOGLEVEL_ERROR 1
#define LOGLEVEL_NONE 0

#if LOG_LEVEL >= LOGLEVEL_DEBUG
    #define LOG_DEBUG(...) fmt::println(">\tDEBUG:\t{}", fmt::format(__VA_ARGS__))
#else
    #define LOG_DEBUG(...)
#endif

#if LOG_LEVEL >= LOGLEVEL_INFO
    #define LOG_INFO(...) fmt::println(">>\tINFO:\t{}", fmt::format(__VA_ARGS__))
#else
    #define LOG_INFO(...)
#endif

#if LOG_LEVEL >= LOGLEVEL_WARN
    #define LOG_WARN(...) fmt::println(">>>\tWARN:\t{}", fmt::format(__VA_ARGS__))
#else
    #define LOG_WARN(...)
#endif

#if LOG_LEVEL >= LOGLEVEL_ERROR
    #define LOG_ERROR(...) fmt::println(">>>>\tERROR:\t{}", fmt::format(__VA_ARGS__))
#else
    #define LOG_ERROR(...)
#endif
