#include "utils.hpp"

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

bool is_service_running(const char *serviceName) {
    Handle handle;
    SmServiceName service_name = smEncodeName(serviceName);
    bool running = R_FAILED(smRegisterService(&handle, service_name, false, 1));

    svcCloseHandle(handle);

    if (!running)
        smUnregisterService(service_name);

    return running;
}

int get_CFW() {
    if(is_service_running("rnx"))       return 0; //ReiNX
    else if(is_service_running("tx"))   return 1; //SXOS
    else                                return 2; // Atmosphere
}

