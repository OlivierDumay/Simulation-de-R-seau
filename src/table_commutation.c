#include "table_commutation.h"

void init_table_commutation(table_commutation *table) {
    table->taille = 0;
}

table_commutation *ajouter_entree(table_commutation *table, const char *mac, int port) {
    for (int i = 0; i < table->taille; i++) {
        if (strcmp(table->entrees[i].mac, mac) == 0) { // Si l'entrée existe déjà, on met à jour le port
            table->entrees[i].port = port;
            return table;
        }
    }
    if (table->taille < MAX_ENTREES) {
        strncpy(table->entrees[table->taille].mac, mac, MAC_LENGTH - 1); // Copie de la MAC
        table->entrees[table->taille].mac[MAC_LENGTH - 1] = '\0';
        table->entrees[table->taille].port = port;
        table->taille++;
    }
    return table;
}

// Recherche d'un port à partir d'une adresse MAC
int rechercher_port(const table_commutation *table, const char *mac) {
    for (int i = 0; i < table->taille; i++) {
        if (strcmp(table->entrees[i].mac, mac) == 0) { // Si l'adresse MAC correspond
            return table->entrees[i].port; // Retourne le port associé
        }
    }
    return -1;
}

// Affichage de la table de commutation
void afficher_table_commutation(const table_commutation *table) {
    printf("Table de commutation :\n");
    for (int i = 0; i < table->taille; i++) {
        printf("MAC : %s | Port : %d\n", table->entrees[i].mac, table->entrees[i].port); // Affiche chaque entrée
    }
}
