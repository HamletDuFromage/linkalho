#ifndef __LINKUSER_UTILS_HPP__
#define __LINKUSER_UTILS_HPP__

#include <switch.h>
#include "constants.hpp"
#include <iostream>

void attempt_reboot();

extern "C" bool is_service_running(const char *serviceName);

extern "C" int get_CFW();

#endif