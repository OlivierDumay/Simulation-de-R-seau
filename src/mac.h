#pragma once

#include <stdint.h>
#include <stdbool.h>

// Définition d'une adresse MAC
typedef int8_t mac[6];

// Affiche l'adresse MAC (format : AA:BB:CC:DD:EE:FF)
void afficherMAC(mac adr);

// Affichage sans possibilite de modification grace a const
void lireMAC(const char* ligne);

// Retourne une chaîne (char*) représentant l'adresse MAC (à libérer par l'appelant)
char* ecrireMAC(mac adr);

// Compare deux adresses MAC, retourne true si elles sont identiques
bool mac_equals(mac a, mac b);