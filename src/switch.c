#include "switch.h"
#include "mac.h"

void main
{
    tabCommutation creerConnexion(mac adresseMac, int port)
    {
        tabCommutation connexion;
        connexion.index=-1;
        memcpy(connexion.adrMac, adresseMac, sizeof(mac));
        connexion.port=port;
        return connexion;
    }
    
    void afficherMAC(mac adresse)
    {
        for (int i = 0; i < 6; i++) 
        {
            printf("%02X", (unsigned char)adresse[i]);
            if (i < 5) 
            {
                printf(":");
            }
        }
        printf("\n");
    }
    
    void supprimerConnexion(int port)
    {
    
    }
    
}