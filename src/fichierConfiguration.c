#include "fichierConfiguration.h"

#include "reseau.h"

#define tMach (r->tabMachine)
#define ttMach (r->nb_machine)
#define tLien (r->tabLien)
#define ttLien (r->nb_lien)

static uint8_t nbSwitch;

void afficheLien (reseau* r)
{

    //initialisation de nbSwitch
    nbSwitch = 0;
    for (int i =0; i < ttMach; i++) 
    {
        if (tMach[i].type == TYPE_SWITCH)
        {nbSwitch++;}
    }
    

    for (int i =0; i < ttLien; i++) // on parcours toutes les lien du réseau
    {
        //printf("Lien: %u , type1: %u , type2: %u, poids: %u\n", i, tLien[i].machine_1.type, tLien[i].machine_2.type, tLien[i].poids);
        if (tLien[i].machine_1.type == TYPE_SWITCH) // si la machine est un switch (on l'appelera switch i)
        {
            //printf("test switch lien %u\n", i);
            af_chercheLAutreMachineDuLien(r, tLien[i].machine_1, tLien[i].machine_2, i);
        }
        
        if (tLien[i].machine_1.type == TYPE_STATION) // si la machine est une station (on l'appelera station i)
        {
            //printf("test station lien %u\n", i);
            af_chercheLAutreMachineDuLien(r, tLien[i].machine_1, tLien[i].machine_2, i);
        }
    }
}

void af_chercheDansLesLiens (reseau* r, machine_t machineDepart, bool* lienPasse)
{
    // on parcours tous les liens, pour chercher si la machine i est dans un lien (on appelera lien j)
    for (int j = 0; j < ttLien; j++)
    {
        if(lienPasse[j])
        {
            //printf("j passé: %u, \n", j);
            if (machineEquals(machineDepart, tLien[j].machine_1)) // si la machine  est la 1ere machine du lien
            {
                // on cherche la deuxieme machine du lien
                af_chercheLAutreMachineDuLien(r, machineDepart,  tLien[j].machine_2, j);
                break;
            }
            if (machineEquals(machineDepart, tLien[j].machine_2)) // si la machine est la 2ere machine du lien
            {
                    // on cherche la 1ere machine du lien
                af_chercheLAutreMachineDuLien(r,  machineDepart, tLien[j].machine_1, j);
                break;
            }
        }
        //printf("Fin de boucle af_chercheDansLesLiens , j: %u\n", j);
    }

}

void af_chercheLAutreMachineDuLien(reseau* r, machine_t machineDepart, machine_t machineArrivee, uint8_t j)
{
    // on parcours encore les machine pour trouver l'index de la machine, index du fichier de configuration, pas index de tabMachine
    for (uint8_t k =0; k < ttMach; k++) 
    {
       // printf("Cherche autre machine2 du lien %u, tMach[%u]?\n", j, k);
        char ret1[23];
        char ret2[23];
        ret1[0] = '\0';
        ret2[0] = '\0';
        ecrireMac(getMac(machineDepart), ret1);
        ecrireMac(getMac(machineArrivee),ret2);
        //printf("MachineDepart : %s , MachineArrivee : %s\n", ret1, ret2);
        if (machineEqualsType(machineArrivee, tMach[k])) // si la machine a le meme type que celle qu'on cherche
        {
            if (machineEquals(tMach[k], machineArrivee)) // si on trouve l'autre machine
            {
                //printf("lien trouvé, machine n°: %u, du type %d\n ", k,  machineArrivee.type);
                af_afficheLeLien(r, j, machineDepart, machineArrivee);
                break;
            }
        }

    }
}
void af_afficheLeLien(reseau* r, uint8_t j, machine_t machineDepart, machine_t machineArrivee)
{
    uint8_t indiceMachineDepart;
    uint8_t indiceMachineArrivee;
    //ajustement de l'indice de machineDepart selon son type
    if (machineDepart.type == TYPE_STATION)
    {indiceMachineDepart = af_ajustementIndice(r, machineDepart);}
    else
    {  indiceMachineDepart = af_ajustementIndice(r, machineDepart);  }
    //ajustement de machineArrivee
    indiceMachineArrivee = af_ajustementIndice(r, machineArrivee);

    // affiche : indice ajusté de machineDepart; indice ajusté de machine arrivé; poids du lien
    printf("%u;%u;%u\n",indiceMachineDepart, indiceMachineArrivee, tLien[j].poids);
}

uint8_t af_ajustementIndice(reseau* r, machine_t machine)
{
    // ajustement de l'indice a afficher dans le lien
    // car si c'est l'indice d'une station, elle est afficher dans le fichier
    // de configuration apres les switch
    // il faut donc y ajouter le nombre de switch
    if (machine.type == TYPE_STATION)
    {
        return nbSwitch + trouveIndiceFicConf(r, machine);
    }
    // sinon c'est un switch donc juste le compteur
    return  trouveIndiceFicConf(r, machine);
}

void afficheLienPasse (bool* lienPasse, reseau* r)
{
    char retLPasse[256];
    retLPasse[0] = '\0';
    strcat(retLPasse, "lienPasse: ");
    for (int i =0; i < r->nb_lien; i++) 
    { 
        char buf[64];
        buf[0] = '\0';
        sprintf(buf, "%u", lienPasse[i]); 
        strcat(retLPasse, buf);
        strcat(retLPasse, ", ");
    }
    printf("%s\n", retLPasse );
}

uint8_t trouveIndiceFicConf (reseau* r, machine_t machineATrouver)
{
    // dans le réseau r, cherche la combien-ieme machine du meme type est la machineATrouver
    uint8_t compteur = -1;
    for (int i = 0; i< r->nb_machine; i++)
    {
        //printf("ttMach dans trouveInd: %u\n", r->nb_machine);
        //printf("trouveIndiceFicConf- i: %u, compteur: %u\n", i, compteur);
        //printf("(machineEqualsType(r->tabMachine[i], machineATrouver) : %b\n", (machineEqualsType(r->tabMachine[i], machineATrouver)));
        if (machineEqualsType(r->tabMachine[i], machineATrouver))
        {
            //printf("Increment compteur\n");
            compteur++;
            if (machineEquals(r->tabMachine[i], machineATrouver))
                {return compteur;}
        }
        //else {printf("type mismatch, i: %u", i);}
    }
    return 253;
}