#pragma once

#include "mac.h"
#include "ip.h"

typedef struct {
    mac adrMac;
    ip adrIp;
} station;

// Copies the MAC address from the station to 'out'
void getMac(station s, mac out);
// Copies the IP address from the station to 'out'
void getIP(station s, ip out);