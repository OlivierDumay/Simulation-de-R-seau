#include "switch.h"

void initSwitch(switch_t* sw, mac mac, int8_t nbPort, int16_t priorite) {
    memcpy(sw->adrMac, mac, 6);
    sw->nbPort = nbPort;
    sw->priorite = priorite;
    sw->tailleTabCommu = 8;
    sw->tabCommu = malloc(sizeof(ligneTabCommutation)*sw->tailleTabCommu);
    
    // Initialisation STP
    sw->is_root_bridge = false;    // Par défaut, pas racine
    sw->root_path_cost = 0;
    memcpy(sw->designated_bridge_id, mac, 6); // Par défaut, soi-même
    sw->root_port = 0;
    sw->received_bpdus = malloc(sizeof(BPDU) * nbPort); // Un BPDU par port max
    sw->bpdu_count = 0;
}

void deinitSwitch(switch_t* sw)
{
    free(sw->tabCommu);
}

void creerConnexion(switch_t* sw, mac adrMac, int port)
{
    ligneTabCommutation l;
    memcpy(l.adrMac, adrMac, sizeof(mac));
    l.port = port;
    //test les la connexion n'existe pas deja
    for (int8_t i = 0; i < sw->nbLigneTabCommu; i++)
    {
        if ( equalsLigneTabCommu(l, sw->tabCommu[i])) 
        { 
            printf("Switch, tabCommu - cette liaison existe deja");
            return;
        }
    }
    // test si table commu pleine ou pas
    if (sw->nbLigneTabCommu == sw->tailleTabCommu-1)
    {
        sw->tailleTabCommu = sw->tailleTabCommu * 2;
        sw->tabCommu  = realloc(sw->tabCommu, sizeof(ligneTabCommutation) * sw->tailleTabCommu);
    }
    memcpy(&sw->tabCommu[sw->nbLigneTabCommu], &l, sizeof(ligneTabCommutation));
    sw->nbLigneTabCommu++;
}

void supprimerConnexion_parMac(switch_t* sw, mac adrMac)
{
    for (int8_t i = 0; i < sw->nbLigneTabCommu; i++)
    {
        if ( macEquals(sw->tabCommu[i].adrMac, adrMac)) // si on trouve l'adresse mac
        {
            for (int8_t j = i; j < sw->nbLigneTabCommu; j++) // on décale tout les element de tabCommu d'un pas vers la gauche, a partir de l
            {
                memcpy(&sw->tabCommu[j], &sw->tabCommu[j+1], sizeof(ligneTabCommutation));
            }
            sw->nbLigneTabCommu--; // on reduit la taille du tabCommu
            break;
        }
    }
    
}
bool equalsLigneTabCommu(ligneTabCommutation l1, ligneTabCommutation l2)
{
    if (macEquals(l1.adrMac, l2.adrMac) && l1.port == l2.port) {return true;}
    return false;
}

int8_t chercheMacDansTabCommu (switch_t* sw, mac adrMac)
{
    for (int8_t i = 0; i < sw->nbLigneTabCommu; i++)
    {
        if ( macEquals(sw->tabCommu[i].adrMac, adrMac)) {return sw->tabCommu[i].port;}
    }
    return -1;
}

void envoyerBPDU(switch_t* sw, int port) {
    BPDU bpdu;
    memcpy(bpdu.root_bridge_id, sw->is_root_bridge ? sw->adrMac : sw->designated_bridge_id, 6);
    bpdu.root_path_cost = sw->root_path_cost;
    memcpy(bpdu.bridge_id, sw->adrMac, 6);
    bpdu.port_id = port;
    
    // Envoyer le BPDU (simulé ici)
    printf("Switch ");
    char mac_str[18];
    ecrireMac(sw->adrMac, mac_str);
    printf("%s envoie BPDU sur le port %d\n", mac_str, port);
}

void resoudreBPDU(switch_t* sw) {
    // Trouver le BPDU avec le meilleur chemin vers la racine
    BPDU best_bpdu;
    bool found = false;
    
    for (int i = 0; i < sw->bpdu_count; i++) {
        if (!found || 
            memcmp(sw->received_bpdus[i].root_bridge_id, best_bpdu.root_bridge_id, 6) < 0 ||
            (memcmp(sw->received_bpdus[i].root_bridge_id, best_bpdu.root_bridge_id, 6) == 0 && 
             sw->received_bpdus[i].root_path_cost < best_bpdu.root_path_cost)) {
            memcpy(&best_bpdu, &sw->received_bpdus[i], sizeof(BPDU));
            found = true;
        }
    }
    
    // Mettre à jour les informations STP
    if (found) {
        if (memcmp(best_bpdu.root_bridge_id, sw->adrMac, 6) == 0) {
            sw->is_root_bridge = true;
        } else {
            sw->is_root_bridge = false;
            memcpy(sw->designated_bridge_id, best_bpdu.root_bridge_id, 6);
            sw->root_path_cost = best_bpdu.root_path_cost + 1; // +1 pour le coût du lien actuel
        }
    }
    
    // Réinitialiser la liste des BPDUs reçus
    sw->bpdu_count = 0;
}

void recevoirBPDU(switch_t* sw, BPDU* bpdu, int port) {
    if (sw->bpdu_count < sw->nbPort) {
        memcpy(&sw->received_bpdus[sw->bpdu_count], bpdu, sizeof(BPDU));
        sw->bpdu_count++;
        
        // Si ce BPDU a un meilleur chemin, déclencher une résolution
        if (memcmp(bpdu->root_bridge_id, sw->designated_bridge_id, 6) < 0 || 
            (memcmp(bpdu->root_bridge_id, sw->designated_bridge_id, 6) == 0 && 
             bpdu->root_path_cost < sw->root_path_cost)) {
            resoudreBPDU(sw);
        }
    }
}