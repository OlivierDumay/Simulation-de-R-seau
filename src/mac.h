#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "traduction.h"

// Définition d'une adresse MAC
typedef uint8_t mac[6];

// string vers mac, le retour est l'adresse du type mac static creer dans la fonction
mac* lireMac(char* ligne);


// mac vers string, Stocke retour dans une chaîne (char*) en argument 
void ecrireMac(mac adr, char ret[23]);


// Compare deux adresses MAC, retourne true si elles sont identiques
bool macEquals(mac a, mac b);