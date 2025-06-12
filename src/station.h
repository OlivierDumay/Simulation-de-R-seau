#pragma once

#include "mac.h"
#include "ip.h"

typedef struct station{
    mac adrMac;
    ip adrIp;
} station;

void initStation(station* s, mac mac, ip ip);
