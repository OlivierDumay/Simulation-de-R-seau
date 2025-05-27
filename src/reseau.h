#pragma once

#include "station.h"
#include "switch.h"

typedef enum {
    TYPE_STATION,
    TYPE_SWITCH
} type_machine;

typedef union {
    station station;
    switch_t sWitch;
} machine;

typedef struct {
    type_machine type;
    machine donnee;
} element_tabMachine;

#define MAX_MACHINES 100

typedef struct {
    element_tabMachine tabSommet[MAX_MACHINES];
    int nombreMachines;
} reseau;

int getNombreMachine(reseau r);
int getNombreConnexion(reseau r);