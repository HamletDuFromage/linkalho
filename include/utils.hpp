#ifndef __LINKUSER_UTILS_HPP__
#define __LINKUSER_UTILS_HPP__

#include <switch.h>
#include <iostream>
#include "constants.hpp"

void attempt_reboot(){
#ifndef DEBUG
    Result rc = bpcInitialize();
    if (R_FAILED(rc))
        printf("bpcInit: %08X\n", rc);
    else
    {
        bpcRebootSystem();
        bpcExit();
    }
#else
    std::cout << "Reboot would happen here" << std::endl;
#endif
}

#endif // __LINKUSER_UTILS_HPP__