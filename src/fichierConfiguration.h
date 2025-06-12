#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "reseau.h"
#include "station.h"
#include "switch.h"
#include "ip.h"
#include "mac.h"
#include "traduction.h"




void afficheLien (reseau* r);
void af_chercheDansLesLiens (reseau* r, machine_t machineDepart, bool* lienPasse);
void af_chercheLAutreMachineDuLien(reseau* r, machine_t machineDepart, machine_t machineArrivee, uint8_t j);
void af_afficheLeLien(reseau* r, uint8_t j, machine_t machineDepart, machine_t machineArrivee);
uint8_t af_ajustementIndice(reseau* r, machine_t machine);
void afficheLienPasse (bool* lienPasse, reseau* r);
uint8_t trouveIndiceFicConf (reseau* r, machine_t machineATrouver);
