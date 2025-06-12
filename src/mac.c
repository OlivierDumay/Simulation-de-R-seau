#include "mac.h"



mac* lireMac(char* ligne)
{
    static mac ret;
    char* avant;
    char* apres;
    extraireChaine(ligne, ':', &avant, &apres);

    ret[0]= (int) strtol(avant, NULL, 16);

    char* reste;
    for (int8_t i = 1; i<5; i++)
    {
        reste = apres;
        extraireChaine(reste, ':', &avant, &apres);
        ret[i] = strtol(avant, NULL, 16);
    }
    ret[5] = strtol(apres, NULL, 16);
    return &ret;
}

void ecrireMac(mac adr, char ret[23])
{
    ret[0] = '\0'; // Initialisation de la chaîne
    for (int i = 0; i < 6; i++)
    {
        char buffer[4];
        uint8versStringHexadecimal(adr[i], buffer);
        strcat(ret, buffer);
        if (i < 5) { strcat(ret, ":"); }
    }
}

bool macEquals(mac a, mac b)
{
    for (int i = 0; i < 6; i++)
    {
        if (a[i] != b[i]) {return false;}       
    }
    return true;
}