#include "ip.h"

void afficherIP(ip adr)
{
  printf("%x,%x,%x,%x,%x,%x,%x,%x",adr[0],adr[1],adr[2],adr[3],adr[4],adr[5],adr[6],adr[7]);
}

ip lireIP(char* adresse_ip)
{
    static ip adresse;

    if (strlen(adresse_ip) < 8) 
    {
        memset(adresse, 0, 8);
        return adresse;
    }

    for(int i=0; i<8;i++)
    {
        adresse[i] = (int8_t)adresse_ip[i];
    }
    return adresse;
}

char* ecrireIP(ip adr)
{
    static char chaine[9];
    for(int i=0; i < 8; i++)
    {
        chaine[i]=(char)adr[i];
    }
    chaine[8] = '\0';
    return chaine;
}

bool equals(ip IP1, ip IP2)
{
    for(int i=0;i<8;i++)
    {
        if(IP1[i]!=IP2[i])
        {
            return false;
        }
    }
    return true;
}

