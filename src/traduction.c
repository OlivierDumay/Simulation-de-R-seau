#include "traduction.h"


void uint8versStringHexadecimal (uint8_t octet, char buffer[3])
{
    sprintf(buffer, "%02x", octet);

}

void extraireChaine(const char* chaine, char separateur, char** avant, char** apres) 
{
char* pos = strchr(chaine, separateur); //& du caractere separateur trouvé en premeir
if (pos != NULL) 
{
    size_t len = pos - chaine; // taille de la chaine jusqu'au séparateur

    *avant = malloc(len + 1); 
    if (!*avant) 
    {
        perror("erreur malloc avant");
    }

    strncpy(*avant, chaine, len); // copie de "chaine" dans "avant", mais seulement jusqu'au séparateur
    (*avant)[len] = '\0';

    *apres = pos + 1; // "apres" est égal a "chaine", mais seulement apres le caractere séparateur
    if (!*apres) 
    {
        perror("erreur malloc apres");
        free(*avant); 
    } 
} 
else 
{
    fprintf(stderr, "Erreur : caractère '%c' non présent dans la chaîne.\n", separateur);
    *avant = NULL;
    *apres = NULL;
}   
}