#include "mac.h"

void afficherMAC(mac adr_mac)
{
    printf("%x,%x,%x,%x,%x,%x,%x,%x",adr[0],adr[1],adr[2],adr[3],adr[4],adr[5]);
}

mac lireMAC(char* adresse_mac)
{
    mac adresse;
    for (int i=0;i<6;i++)
    {
        adresse[i] = (int8_t)adresse_mac[i];
    }
    return adresse;
}

char* ecrireMAC(mac adr)
{
    char chaine[7];
    for(int i=0;i<6;i++)
    {
        chaine[i]=(char)adr[i];
    }
    chaine[7]="\0";
    return chaine;
}

bool equals(mac MAC1, mac MAC2)
{

    for(int i=0;i<6;i++)
    {
        if(MAC1[i]!=MAC2[i])
        {
            return false;
        }
    }
    return true;
}
