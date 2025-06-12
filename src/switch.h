#pragma once

#include "mac.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    mac root_bridge_id;      // Identifiant du bridge racine
    uint32_t root_path_cost; // Coût cumulé jusqu'au root
    mac bridge_id;           // Identifiant du bridge émetteur
    uint8_t port_id;         // Port d'émission
} BPDU;

// vers le port x, il y a la machine adrMac
typedef struct ligneTabCommutation {
    mac adrMac;
    int8_t port;
} ligneTabCommutation;

typedef struct switch_t {
    mac adrMac;
    int8_t nbPort;
    int16_t priorite;
    ligneTabCommutation* tabCommu; // pointer to table of commutations
    int8_t nbLigneTabCommu;
    int8_t tailleTabCommu;       // number of entries in the table

    // Ajouts pour STP
    bool is_root_bridge;
    uint32_t root_path_cost;
    mac designated_bridge_id;
    uint8_t root_port;
    BPDU* received_bpdus;    // Tableau des BPDUs reçus
    uint8_t bpdu_count;
} switch_t;




void initSwitch(switch_t* sw, mac mac, int8_t nbPort, int16_t priorite);
void deinitSwitch(switch_t* sw);

void creerConnexion(switch_t* sw, mac adrMac, int port);
void supprimerConnexion_parMac(switch_t* sw, mac adrMac); // cherche l'adresse mac dans une ligne de la tabCommu, et supprime la ligne si elle est trouvé
bool equalsLigneTabCommu(ligneTabCommutation l1, ligneTabCommutation l2);

int8_t chercheMacDansTabCommu (switch_t* sw, mac adrMac); // si mac dans la tabCommu, retourne le port, sinon retourne -1
int8_t cherchePortDansTabCommu (switch_t* sw, mac adrMac); // si mac dans la tabCommu, retourne le port, sinon retourne -1

void envoyerBPDU(switch_t* sw, int port);
void resoudreBPDU(switch_t* sw);
void recevoirBPDU(switch_t* sw, BPDU* bpdu, int port);
