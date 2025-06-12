#include "ip.h"
#include "mac.h"
#include "reseau.h"
#include "station.h"
#include "switch.h"
#include "test.h"
#include "ethernet.h"
#include "table_commutation.h"

#include <string.h>
#include <stdio.h>

int main() {

    /*
    // test lireMac
    char* strmac = "01:45:23:a6:f7:a2";
    printf("Test: ardMac = lireMac(%s)\n", strmac);
    mac* adrMac = lireMac(strmac);
    char ret[23];
    ecrireMac(*adrMac, ret);
    printf("ecrireMac(adrMac) : %s \n", ret);
    */

         /*
    // test lireIp
    char* strip = "130.79.80.1";
    printf("Test: adrIp = lireMac(%s)\n", strip);
    ip* adrIp = lireIp(strip);
    char ret[20];
    ecrireIp(*adrIp, ret);
    printf("ecrireIp(adrIp) : %s \n", ret);
    */

    
   
    FILE* f = fopen("mylan.lan", "r"); // ouverture lecture
    if (f == NULL)
        {perror ("Erreur ouverture de fichier");
        return 1;}

    reseau r;
    initReseau(&r);
    
    remplirReseauAvecFichier(f, &r);
    
    fclose(f);
    
    printf("lien");

    affichageReseau(&r);
    deinitReseau(&r);









    /*
    // test affiche reseau
    reseau reseau1;
    initReseau(&reseau1);

    station station1;
    mac mac1 = {10,2,30,4,50,6};
    ip ip1 = {126, 0, 0 ,33};
    memcpy(station1.adrMac, mac1, sizeof(mac));
    memcpy(station1.adrIp, ip1, sizeof(ip));
    machine_t machine1;
    machine1.type = TYPE_STATION;
    machine1.donnee.station = station1;

    station station2;
    mac mac2 = {1,20,3,40,5,60};
    ip ip2 = {198, 0, 7 ,33};
    memcpy(station2.adrMac, mac2, sizeof(mac));
    memcpy(station2.adrIp, ip2, sizeof(ip));
    machine_t machine2;
    machine2.type = TYPE_STATION;
    machine2.donnee.station = station2;

    switch_t switch1;
    mac mac3 = {10,222,30,150,25,60};

    tabCommutation tabComm1;
    tabComm1.index = 0;
    tabComm1.port= 2;
    memcpy(tabComm1.adrMac, mac3, sizeof(mac));

    memcpy(switch1.adrMac, mac3, sizeof(mac));
    switch1.nbPort = 4;
    switch1.priorite = 11;
    switch1.tailleTabCommu = 8;
    switch1.tabCommu = malloc(sizeof(tabCommutation)*8);
    switch1.tabCommu[0] = tabComm1;
    machine_t machine3;
    machine3.type = TYPE_SWITCH;
    machine3.donnee.switchs = switch1;

    lien l = initLien(machine1, machine2, 4);
    lien l1 = initLien(machine3, machine2, 4);
    lien l2 = initLien(machine3, machine1, 4);
    
    printf("Test ecrireIp : %b\n", testEcrireIp());
    printf("Test ecrireMac : %b\n", testEcrireMac());


    ajouterMachine(&reseau1, machine1);
    ajouterMachine(&reseau1, machine3);
    ajouterMachine(&reseau1, machine2);
    ajouterLien(&reseau1, l);
    ajouterLien(&reseau1, l1);
    ajouterLien(&reseau1, l2);

    affichageReseau(&reseau1);

    deinitReseau(&reseau1);
    */


    /* test machineEquals
    printf("test true machineEquals(machine1, l.machine_1) : %b\n\n", machineEquals(machine1, l.machine_1));
    printf("test false machineEquals(machine1, l.machine_2): %b\n\n", machineEquals(machine1, l.machine_2));
    printf("test false machineEquals(machine1, l2.machine_1): %b\n\n", machineEquals(machine1, l2.machine_1));
    printf("machineEqualsType(machine1,machine2) : %b\n", machineEqualsType(machine1,machine2));
    printf("machineEqualsType(machine1,machine3) : %b\n", machineEqualsType(machine1,machine3));
    printf("machineEqualsType(machine3,machine2) : %b\n", machineEqualsType(machine3,machine2));

    printf("test true machineEquals(machine3, l2.machine_1) : %b\n", machineEquals(machine3, l2.machine_1));
    */

    //printf("(machineEqualsType(reseau1->tabMachine[0], machine1) : %b\n", (machineEqualsType(reseau1.tabMachine[0], machine1) ));
    //printf("ttMach dans main: %u\n", reseau1.nb_machine);
    //printf("\nTest trouveIndiceFicConf(reseau1, machine1) %u\n\n",trouveIndiceFicConf(&reseau1, machine1));
    //printf("Test trouveIndiceFicConf(reseau1, machine3) %u\n\n",trouveIndiceFicConf(&reseau1, machine3));
    //printf("Test trouveIndiceFicConf(reseau1, machine2) %u\n",trouveIndiceFicConf(&reseau1, machine2));

    /* //test extraireChaine
    char* chaine = "192:168.0.1";
    char* avant;
    char* apres;
    extraireChaine(chaine, ':', &avant, &apres);
    printf("test extraire chaine\n %s\n extraireChaine(chaine, ':', &avant, &apres) :\navant: %s\napres : %s\n", chaine , avant, apres );
    */

    // === TESTS table_commutation ===
    printf("\n--- Test table_commutation ---\n");

    table_commutation table;

    init_table_commutation(&table);

    ajouter_entree(&table, "AA:BB:CC:DD:EE:01", 1);
    ajouter_entree(&table, "AA:BB:CC:DD:EE:02", 2);
    ajouter_entree(&table, "AA:BB:CC:DD:EE:03", 3);

    afficher_table_commutation(&table);

    int port = rechercher_port(&table, "AA:BB:CC:DD:EE:02");
    printf("Port trouvé pour AA:BB:CC:DD:EE:02 : %d (attendu 2)\n", port);

    port = rechercher_port(&table, "AA:BB:CC:DD:EE:FF");
    printf("Port trouvé pour AA:BB:CC:DD:EE:FF : %d (attendu -1)\n", port);

    // === TESTS ethernet ===
    printf("\n--- Test ethernet ---\n");

    uint8_t preambule[ETHERNET_PREAMBULE_SIZE] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    uint8_t dest[ETHERNET_MAC_SIZE] = {0, 1, 2, 3, 4, 5};
    uint8_t src[ETHERNET_MAC_SIZE] = {10, 11, 12, 13, 14, 15};
    uint8_t data[5] = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4};
    uint8_t fcs[ETHERNET_FCS_SIZE] = {0xFF, 0xFE, 0xFD, 0xFC};

    ethernet_frame trame;
    init_ethernet_frame(&trame);
    remplir_trame_ethernet(&trame, preambule, 0xAB, dest, src, 0x0800, data, 5, fcs);
    afficher_trame_ethernet(&trame);
    afficher_trame_ethernet_hex(&trame);

    return 0;
}