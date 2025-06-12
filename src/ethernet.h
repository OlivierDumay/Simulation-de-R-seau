#pragma once

#include <stdint.h>
#include <stddef.h>

// Taille des différents champs d'une trame Ethernet
#define ETHERNET_PREAMBULE_SIZE 7    // Préambule : 7 octets
#define ETHERNET_SFD_SIZE 1          // SFD : 1 octet
#define ETHERNET_MAC_SIZE 6          // Adresse MAC : 6 octets
#define ETHERNET_TYPE_SIZE 2         // Type : 2 octets
#define ETHERNET_MAX_DATA_SIZE 1500  // Données : max 1500 octets
#define ETHERNET_FCS_SIZE 4          // FCS : 4 octets

// Structure d'une trame Ethernet
typedef struct {
    // Préambule (7 octets)
    uint8_t preambule[ETHERNET_PREAMBULE_SIZE];
    
    // SFD (1 octet)
    uint8_t sfd;
    
    // Adresse destination (6 octets)
    uint8_t adresse_destination[ETHERNET_MAC_SIZE];
    
    // Adresse source (6 octets)
    uint8_t adresse_source[ETHERNET_MAC_SIZE];
    
    // Type (2 octets)
    uint16_t type;
    
    // Données (0 à 1500 octets)
    uint8_t data[ETHERNET_MAX_DATA_SIZE];
    size_t data_length;
    
    // FCS (4 octets)
    uint8_t fcs[ETHERNET_FCS_SIZE]; 
} ethernet_frame;

void init_ethernet_frame(ethernet_frame* trame);

void remplir_trame_ethernet(
    ethernet_frame* trame,
    const uint8_t* preambule,
    uint8_t sfd,
    const uint8_t* dest,
    const uint8_t* src,
    uint16_t type,
    const uint8_t* data,
    size_t data_length,
    const uint8_t* fcs
);

// Fonctions pour afficher une trame
void afficher_trame_ethernet(const ethernet_frame* trame);     // affiche la trame en décimal
void afficher_trame_ethernet_hex(const ethernet_frame* trame); // affiche la trame en hexadécimal
