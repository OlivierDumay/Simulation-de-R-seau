#include "reseau.h"

void initReseau(reseau* r)
{
    // initialise les champs
    r-> nb_machine = 0;
    r -> nb_lien = 0;
    r -> lien_capacite = 8;
    r -> tabMachine = malloc (sizeof(lien) * r->lien_capacite);
}
void deinitReseau(reseau* r)
{
    free (r->tabMachine);
}

uint8_t getNombreMachine(reseau* const r)
{
    return r->nb_machine;
}

uint8_t getNombreConnexion(reseau* const r)
{
    return r->nb_lien;
}

//void ajouterMachine (reseau* r, machine_t m)
//bool existeLien (reseau* const g, lien l)
//void ajouterLien (reseau* r, lien l)

//void initLien(machine_t m1, machine_t m2)
