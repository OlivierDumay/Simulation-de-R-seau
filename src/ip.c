#include "ip.h"



ip* lireIp(char* ligne) // string vers ip, le retour est l'adresse de l'ip static creer dans la fonction
{
    static ip ret;
    char* avant;
    char* apres;
    char* reste;
    extraireChaine(ligne, '.', &avant, &apres);
    ret[0] = atoi(avant);

    reste = apres;
    extraireChaine(reste, '.', &avant, &apres);
    ret[1] = atoi(avant);

    reste = apres;
    extraireChaine(reste, '.', &avant, &apres);
    ret[2] = atoi(avant);

    ret[3] = atoi(apres);


    return &ret;
}

void ecrireIp(ip adr, char ret[20]) // ip vers string
{
    sprintf(ret, "%u.%u.%u.%u", adr[0], adr[1], adr[2], adr[3]);
}

bool ip_equals(ip a, ip b)
{
    for (int i = 0; i < 4; i++)
        {
            if (a[i] != b[i]) {return false;}       
        }
        return true;
}