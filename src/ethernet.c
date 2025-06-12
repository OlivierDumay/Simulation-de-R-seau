#include <stdio.h>
#include "ethernet.h"

void init_ethernet_frame(ethernet_frame* trame) {
    for (int i = 0; i < ETHERNET_PREAMBULE_SIZE; i++) trame->preambule[i] = 0;
    trame->sfd = 0;
    for (int i = 0; i < ETHERNET_MAC_SIZE; i++) {
        trame->adresse_destination[i] = 0;
        trame->adresse_source[i] = 0;
    }
    trame->type = 0;
    trame->data_length = 0;
    for (size_t i = 0; i < sizeof(trame->data); i++) trame->data[i] = 0;
    for (int i = 0; i < ETHERNET_FCS_SIZE; i++) trame->fcs[i] = 0;
}

// Affiche une trame Ethernet de manière lisible
void afficher_trame_ethernet(const ethernet_frame* trame) {
    size_t i;
    
    printf("=== Trame Ethernet ===\n");
    
    // Affiche le préambule
    printf("Préambule : ");
    for (i = 0; i < ETHERNET_PREAMBULE_SIZE; i++) {
        printf("%02x ", trame->preambule[i]);
    }
    printf("\n");
    
    // Affiche le SFD
    printf("SFD : %02x\n", trame->sfd);
    
    // Affiche l'adresse destination
    printf("Adresse destination : ");
    for (i = 0; i < ETHERNET_MAC_SIZE; i++) {
        printf("%02x", trame->adresse_destination[i]);
        if (i < ETHERNET_MAC_SIZE - 1) {
            printf(":");
        }
    }
    printf("\n");
    
    // Affiche l'adresse source
    printf("Adresse source : ");
    for (i = 0; i < ETHERNET_MAC_SIZE; i++) {
        printf("%02x", trame->adresse_source[i]);
        if (i < ETHERNET_MAC_SIZE - 1) {
            printf(":");
        }
    }
    printf("\n");
    
    // Affiche le type
    printf("Type : 0x%04x\n", trame->type);
    
    // Affiche les données
    printf("Données (%zu octets) : ", trame->data_length);
    for (i = 0; i < trame->data_length; i++) {
        printf("%02x ", trame->data[i]);
    }
    printf("\n");
    
    // Affiche le FCS
    printf("FCS : ");
    for (i = 0; i < ETHERNET_FCS_SIZE; i++) {
        printf("%02x ", trame->fcs[i]);
    }
    printf("\n");
    
    printf("=====================\n");
}

// Affiche une trame Ethernet en hexadécimal
void afficher_trame_ethernet_hex(const ethernet_frame* trame) {
    size_t i;  // Variable pour les boucles
    
    // Affiche le préambule
    for (i = 0; i < ETHERNET_PREAMBULE_SIZE; i++) {
        printf("%02x ", trame->preambule[i]);
    }
    
    // Affiche le SFD
    printf("%02x ", trame->sfd);
    
    // Affiche l'adresse destination
    for (i = 0; i < ETHERNET_MAC_SIZE; i++) {
        printf("%02x ", trame->adresse_destination[i]);
    }
    
    // Affiche l'adresse source
    for (i = 0; i < ETHERNET_MAC_SIZE; i++) {
        printf("%02x ", trame->adresse_source[i]);
    }
    
    // Affiche le type
    printf("%02x %02x ", (trame->type >> 8) & 0xFF, trame->type & 0xFF);
    
    // Affiche les données
    for (i = 0; i < trame->data_length; i++) {
        printf("%02x ", trame->data[i]);
    }
    
    // Affiche le FCS
    for (i = 0; i < ETHERNET_FCS_SIZE; i++) {
        printf("%02x ", trame->fcs[i]);
    }
    
    printf("\n");
}

// Remplit une trame Ethernet avec des données
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
)
{
    for (int i = 0; i < ETHERNET_PREAMBULE_SIZE; i++) trame->preambule[i] = preambule[i];
    trame->sfd = sfd;
    for (int i = 0; i < ETHERNET_MAC_SIZE; i++) {
        trame->adresse_destination[i] = dest[i];
        trame->adresse_source[i] = src[i];
    }
    trame->type = type;
    trame->data_length = data_length;
    for (size_t i = 0; i < data_length; i++) trame->data[i] = data[i];
    for (int i = 0; i < ETHERNET_FCS_SIZE; i++) trame->fcs[i] = fcs[i];
}