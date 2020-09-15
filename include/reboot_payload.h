#ifndef __REBBOT_PAYLOAD_H__
#define __REBBOT_PAYLOAD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <switch.h>

enum CFW{
    ams,
    rnx,
    sxos,
};

bool is_service_sunning(const char *serviceName);

enum CFW get_CFW();

int reboot_to_payload();

#ifdef __cplusplus
}
#endif

#endif