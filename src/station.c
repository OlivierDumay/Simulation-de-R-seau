#include "station.h"

void initStation(station* s, mac mac, ip ip)
{
    memcpy(s->adrMac, mac, 6); // 6 et pas sizeof(mac) parceque avec memcpy ca retourne la taille de int8_t* , et pas int8_t[6]
    memcpy(s->adrIp, ip, 4); // idem 

}
