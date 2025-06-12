#pragma once

#include <stdio.h>
#include <string.h>

#define MAX_ENTREES 100
#define MAC_LENGTH 18

typedef struct {
    char mac[MAC_LENGTH];
    int port;
} entree_table_commutation;

typedef struct {
    entree_table_commutation entrees[MAX_ENTREES];
    int taille;
} table_commutation;

void init_table_commutation(table_commutation *table);
table_commutation *ajouter_entree(table_commutation *table, const char *mac, int port);
int rechercher_port(const table_commutation *table, const char *mac);
void afficher_table_commutation(const table_commutation *table);