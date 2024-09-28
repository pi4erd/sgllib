#include <fmt/base.h>
#include <log.hpp>

int Logging::LOG_LEVEL = 0;

void set_log_level(int log_level) {
    Logging::LOG_LEVEL = log_level;
}
