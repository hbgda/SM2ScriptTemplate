#include "logging.h"

#include <stdio.h>
#include <stdarg.h>
#include <sstream>

#include "include/termcolor.h"

namespace logging {
    void log(const LogLevel level, const char* fmt, ...) {
        switch (level) {
            case LogLevel::INFO:
                std::cout << termcolor::white << "[INFO ]: ";
                break;
            case LogLevel::WARN:
                std::cout << termcolor::yellow << "[WARN ]: ";
                break;
            case LogLevel::DEBUG:
                std::cout << termcolor::bright_grey << "[DEBUG]: ";
                break;
            case LogLevel::FATAL:
                std::cout << termcolor::red << "[FATAL]: ";
                break;
            default:
                break;
        }

        va_list vargs;
        va_start(vargs, fmt);
        vprintf(fmt, vargs);

        std::cout << termcolor::reset << std::endl;
    }
}