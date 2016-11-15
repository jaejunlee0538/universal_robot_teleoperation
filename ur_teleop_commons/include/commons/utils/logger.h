//
// Created by ub1404 on 15. 8. 14.
//

#ifndef COMMMODULE_LOGGER_H
#define COMMMODULE_LOGGER_H

#include "stdio.h"


#define VERBOSE2    7
#define VERBOSE1    6
#define DEBUG       5
#define FATAL       4
#define ERROR       3
#define WARNNING    2
#define INFO        1
#define NO_LOG      0

#ifndef LOG_LEVEL
#define LOG_LEVEL FATAL
#endif

#define LOG(level, format, ...) \
do \
{ \
  printf(level); \
  printf(format, ##__VA_ARGS__); \
  printf("\n"); \
} while (0)

#if LOG_LEVEL >= VERBOSE2
#define LOG_VERBOSE2(format, ...) LOG("[VERBOSE] ", format, ##__VA_ARGS__)
#else
#define LOG_VERBOSE2(format, ...)
#endif

#if LOG_LEVEL >= VERBOSE1
#define LOG_VERBOSE1(format, ...) LOG("[VERBOSE] ", format, ##__VA_ARGS__)
#else
#define LOG_VERBOSE1(format, ...)
#endif

#if LOG_LEVEL >= DEBUG
#define LOG_DEBUG(format, ...) LOG("[DEBUG] ", format, ##__VA_ARGS__)
#else
#define LOG_DEBUG(foramt, ...)
#endif

#if LOG_LEVEL >= FATAL
#define LOG_FATAL(format, ...) LOG("[FATAL] ", format, ##__VA_ARGS__)
#else
#define LOG_FATAL(format, ...)
#endif

#if LOG_LEVEL >= ERROR
#define LOG_ERROR(format, ...) LOG("[ERROR] ", format, ##__VA_ARGS__)
#else
#define LOG_ERROR(format, ...)
#endif

#if LOG_LEVEL >= WARNNING
#define LOG_WARN(format, ...)  LOG("[WARNING] ", format, ##__VA_ARGS__)
#else
#define LOG_WARN(format, ...)
#endif

#if LOG_LEVEL >= INFO
#define LOG_INFO(format, ...)  LOG("[INFO] ", format, ##__VA_ARGS__)
#else
#define LOG_INFO(format, ...)
#endif

#endif //COMMMODULE_LOGGER_H
