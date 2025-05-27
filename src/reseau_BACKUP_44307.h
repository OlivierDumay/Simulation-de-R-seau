#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "station.h"
#include "switch.h"

// def enumeration de machine, pour test le type de l'union machine_u
typedef enum machine_e{
  TYPE_STATION ,
  TYPE_SWITCH 
} machine_e;

// def union de type station et type switch
typedef union machine_u {
    station station;
    switch_t switchs;
}machine_u ;

//def structure qui joint les types station et switch
typedef struct machine_t{
    machine_e type;
    machine_u donnee;
}machine_t;


// def de lien entre les machines (arete)
typedef struct lien {
    machine_t machine_1;
    machine_t machine_2;
}lien;




// def reseau (graphe)
typedef struct reseau{
    uint8_t nb_machine;
    uint8_t nb_lien;
    uint8_t lien_capacite;
    machine_t* tabMachine;
    // tab[0].type = TYPE_STATION
    // tab[0].donnee.station.adrMac =...
    // tab[0].donnee.station.adrIP=...
    //
    // tab[1].type = TYPE_SWITCH;
    // tab[1].donnee.switch.adrMac = ...;
    // tab[1].donnee.switch.nbPort = ...;
    // tab[1].donnee.switch.priorite = ..;
    // tab[1].donnee.switch.tabCommu = .. ;
    

}reseau;

void initReseau(reseau* r);
void deinitReseau(reseau* r);

uint8_t getNombreMachine(reseau* const r);
uint8_t getNombreConnexion(reseau* const r);

void ajouterMachine (reseau* const r, machine_t m);
bool existeLien (reseau* const r, lien l);
void ajouterLien (reseau* const r, lien l);

void initLien(machine_t m1, machine_t m2);
