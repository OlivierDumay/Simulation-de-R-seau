#pragma once

#include <stdint.h> // Pour int8_t
#include <stdio.h>  // Pour printf
#include <stdbool.h> // Pour bool
#include <string.h>

#include "traduction.h"

// Définition d'une adresse IP
typedef uint8_t ip[4];

// string vers ip, le retour est l'adresse de l'ip static creer dans la fonction
ip* lireIp(char* ligne);

// ip vers string, Stocke retour dans une chaîne (char*) en argument 
void ecrireIp(ip adr, char ret[20]);

// Compare deux ip, retourne vrai si identique
bool ip_equals(ip a, ip b);

