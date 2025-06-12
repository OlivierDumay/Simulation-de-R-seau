#include "reseau.h"

#include "fichierConfiguration.h"

void initReseau(reseau* r)
{
    // initialise les champs
    r-> nb_machine = 0;
    r -> nb_lien = 0;
    r -> lien_capacite = 8;
    r -> machine_capacite = 8;
    r -> tabLien = malloc (sizeof(lien) * r->lien_capacite);
    r -> tabMachine = malloc (sizeof(machine_t) * r->machine_capacite);
}
void deinitReseau(reseau* r)
{
    free (r->tabLien);
    free (r->tabMachine);
}
void affichageReseau(reseau* r)
{
    printf("%u %u\n", r->nb_machine, r->nb_lien); // entete

    //uint8_t compteurDesSwitchs = 0; // nb de switch, pour index qui fait reference au fichier de configuration, pas l'index de r->tabmachine
    
    // afficher d'abord tous les switchs (2)
    for (int i = 0; i < r->nb_machine; i++) //mac, nbport, prio
    {
        if (r->tabMachine[i].type == TYPE_SWITCH)
        {
            //compteurDesSwitchs++;

            char* ligne = (char*) malloc(64*sizeof(char));
            ligne[0] = '\0';
            strcat(ligne, "2;");

            char bufMac[18];
            bufMac[0] = '\0';
            ecrireMac(r->tabMachine[i].donnee.switchs.adrMac, bufMac);
            strcat(ligne, bufMac);
            strcat(ligne, ";");

            char buffer[8];
            buffer[0] = '\0';
            sprintf(buffer, "%u", r->tabMachine[i].donnee.switchs.nbPort);
            strcat(ligne, buffer);
            strcat(ligne, ";");

            sprintf(buffer, "%u", r->tabMachine[i].donnee.switchs.priorite);
            strcat(ligne, buffer);
            //printf("Priorité à l'affichage : %s\nr->tabMachine[i].donnee.switchs.priorite : %u\n", buffer, r->tabMachine[i].donnee.switchs.priorite);

            printf("%s\n", ligne);
            free (ligne);
            continue;
        }
    }
    // puis afficher les station (1)
    for (int i =0; i < r->nb_machine; i++) //mac, ip
    {
        if (r->tabMachine[i].type == TYPE_STATION)
        {
            //char ligne[64]; // a voir si taille cohérente
            char* ligne = (char*) malloc(128*sizeof(char));
            ligne[0] = '\0';

            strcat(ligne, "1;");
            char bufMac[18];
            bufMac[0] = '\0';
            ecrireMac(r->tabMachine[i].donnee.station.adrMac, bufMac);
            strcat(ligne, bufMac);
 
            strcat(ligne, ";");

            char bufIP[20];
            bufIP[0] = '\0';
            ecrireIp(r->tabMachine[i].donnee.station.adrIp, bufIP);
            strcat(ligne, bufIP);
            printf("%s\n", ligne);
            free(ligne);
            continue;
        }
    }
    
    // enfin afficher les liens
    afficheLien(r);
    simulerSTP(r);
    
}
void remplirReseauAvecFichier (FILE* fichier, reseau* r)
{

    char ligne [256];

    uint8_t compteurLigne = 0;
    uint8_t nMachine = 0;
    uint8_t nLien = 0;
    
    while((fgets(ligne, sizeof(ligne), fichier)) != NULL)
    {
        char* apres1;
        char* apres2;
        compteurLigne++;
        //printf("DEBUG ligne %d : %s", compteurLigne, ligne);

        // l'entete, recupere le nombre de machine et lien
        if (compteurLigne == 1)
        {
            char* snMachine;

            extraireChaine(ligne, ' ', &snMachine, &apres1);
            nMachine = atoi(snMachine);
            nLien = atoi(apres1);
        }

        // pour les ligne des machine
        if (compteurLigne >1 && compteurLigne <= nMachine + 1)  // si ligne de machine
        {
           //test si machine est station ou switch
            char* stype;
            printf("ligne %u:    %s",compteurLigne, ligne);
            extraireChaine(ligne, ';', &stype, &apres1);

            if (strcmp(stype,"2") == 0) // la machine est un switch
            {
                
                char* smac;
                extraireChaine(apres1, ';', &smac, &apres2);
                char* snPort;
                extraireChaine(apres2, ';', &snPort, &apres1);
                char* sPriorite = apres1;
                //printf("smac : %s\nnport : %s\nsPriorite : %s\n", smac, snPort, sPriorite);

                //init du switch
                switch_t s;
                mac* adrMac = lireMac(smac);
                int8_t nPort = atoi(snPort);
                int16_t priorite = atoi(sPriorite);
                initSwitch(&s, *adrMac, nPort, priorite);
                //printf("intpriorité : %u\n", priorite);
                
                // inseré dans une machine
                machine_t m = initMachineSwitch(s);

                // inseré dans le reseau
                ajouterMachine(r, m);
            }

            if (strcmp(stype,"1") == 0) // la machine est un switch
            {
                char* smac;
                extraireChaine(apres1, ';', &smac, &apres2);
                char* sip = apres2;
                //printf("smac : %s\nsip : %s\n", smac, sip);

                //init de la station
                station s;
                mac* adrMac = lireMac(smac);
                ip* adrIp = lireIp(sip);
                initStation(&s, *adrMac, *adrIp);

                
                // inseré dans une machine
                machine_t m = initMachineStation(s);

                // inseré dans le reseau
                ajouterMachine(r, m);
            }
        }

        // pour les ligne des liens
        if (compteurLigne > nMachine + 1 && compteurLigne <= nMachine + nLien + 1)  // si ligne de lien
        {
            char* sm1;
            char* sm2;
            char* spoids;
            char* apres;
            char* reste;
            printf("ligne %u:    %s",compteurLigne, ligne);
            extraireChaine(ligne, ';', &sm1, &apres);
            reste = apres;
            extraireChaine(reste, ';', &sm2, &apres);
            spoids = apres;

            // init lien
            int8_t indiceM1 = atoi(sm1);
            int8_t indiceM2 = atoi(sm2);
            int8_t intPoids = atoi(spoids);
            
            printf("indicem1 : %u, indicem2: %u\n", indiceM1, indiceM2);
            lien l = initLien(r->tabMachine[indiceM1], r->tabMachine[indiceM2], intPoids);

            // inseré dans reseau
            ajouterLien(r, l);
        }

    }
}

machine_t initMachineStation (station s) // la station doit etre initialisé avant
{
    machine_t m;
    m.type = TYPE_STATION;
    m.donnee.station = s;
    return m;
}
machine_t initMachineSwitch (switch_t s) // la station doit etre initialisé avant
{
    machine_t m;
    m.type = TYPE_SWITCH;
    m.donnee.switchs = s;
    return m;
}
uint8_t getNombreMachine(reseau* const r)
{
    return r->nb_machine;
}
void ajouterMachine (reseau* r, machine_t m) 
{
    if(r->nb_machine == r->machine_capacite-1)
    {
        r->machine_capacite = r->machine_capacite * 2;
        r->tabMachine = realloc (r->tabMachine, sizeof(machine_t) * r->machine_capacite); 
    }
    r->tabMachine[r->nb_machine] = m;
    r->nb_machine++;
}
bool machineEquals (machine_t m1, machine_t m2)
{
    if (machineEqualsType(m1, m2))
    {
        if (m1.type == TYPE_STATION)
        {
            /* test pour dev, a supprimmer
            char ret1[23], ret2[23];
            ret1[0] = '\0';
            ret2[0] = '\0';

            ecrireMac(m1.donnee.station.adrMac, ret1 );
            ecrireMac(m2.donnee.station.adrMac, ret2 );
            printf("machineEquals if : m1.adrmac = %s, m2.adrmac = %s \n" , ret1 , ret2);
            */
            if (macEquals(m1.donnee.station.adrMac,m2.donnee.station.adrMac)) { return true;}   
        }
        if (m1.type == TYPE_SWITCH)
        {
            if (macEquals(m1.donnee.switchs.adrMac, m2.donnee.switchs.adrMac)) {return true;}
        }
    }
    return false;
}
bool machineEqualsType (machine_t m1, machine_t m2)
{
        //printf("[compare Type] m1.type = %d, m2.type = %d\n", m1.type, m2.type);
        return (m1.type == m2.type);
}
mac* getMac(machine_t m)
{
    static mac ret;
    if (m.type == TYPE_SWITCH)
    {
        memcpy(ret, m.donnee.switchs.adrMac, 6);
    }
    if (m.type == TYPE_STATION)
    {
        memcpy(ret, m.donnee.station.adrMac, 6);
    }
    return &ret;
}

lien initLien(machine_t m1, machine_t m2, uint8_t poids) {
    lien l;
    l.machine_1 = m1;
    l.machine_2 = m2;
    l.poids = poids;
    l.machine_1_port = 0; // ou la valeur appropriée
    l.machine_2_port = 0; // ou la valeur appropriée
    return l;
}
uint8_t getNombreConnexion(reseau* const r)
{
    return r->nb_lien;
}
bool existeLien (reseau* const r, lien l)
{
    for (size_t i =0; i < r ->nb_lien; i++)
    {
        if (lienEquals(r->tabLien[i], l)) {return true;}
    }
    return false;
}
void ajouterLien (reseau* const r, lien l) 
{
    if(r->nb_lien == r->lien_capacite-1)
    {
        r->lien_capacite = r->lien_capacite * 2;
        r->tabLien = realloc (r->tabLien, sizeof(machine_t) * r->lien_capacite); 
    }
    r->tabLien[r->nb_lien] = l;
    r->nb_lien ++; 
}
bool lienEquals (lien l1, lien l2)
{
    machine_t l1m1 = l1.machine_1;
    machine_t l1m2 = l1.machine_2;
    machine_t l2m1 = l2.machine_1;
    machine_t l2m2 = l2.machine_2;

    // cas 1: l1.m1 == l2.m1 et l1.m2 == l2.m2
    if (machineEquals(l1m1, l2m1) && machineEquals(l1m2, l2m2)) {return true;}
    // cas 2: l1.m1 == l2.m2 et l1.m2 == l2.m1
    if (machineEquals(l1m1, l2m2) && machineEquals(l1m2, l2m1)) {return true;}
    return false;
}

void electRootBridge(reseau* r) {
    if (r->nb_machine == 0) return;

    // Trouver le switch avec la plus haute priorité (valeur la plus basse)
    machine_t* root = NULL;
    for (int i = 0; i < r->nb_machine; i++) {
        if (r->tabMachine[i].type == TYPE_SWITCH) {
            if (root == NULL || 
                r->tabMachine[i].donnee.switchs.priorite < root->donnee.switchs.priorite ||
                (r->tabMachine[i].donnee.switchs.priorite == root->donnee.switchs.priorite &&
                 memcmp(r->tabMachine[i].donnee.switchs.adrMac, root->donnee.switchs.adrMac, 6) < 0)) {
                root = &r->tabMachine[i];
            }
        }
    }

    // Définir comme root bridge
    if (root) {
        root->donnee.switchs.is_root_bridge = true;
        root->donnee.switchs.root_path_cost = 0;
        memcpy(root->donnee.switchs.designated_bridge_id, root->donnee.switchs.adrMac, 6);
    }
}

void simulerSTP(reseau* r) {
    // Étape 1: Élection du root bridge
    electRootBridge(r);
    
    // Étape 2: Les switches envoient des BPDUs
    for (int i = 0; i < r->nb_machine; i++) {
        if (r->tabMachine[i].type == TYPE_SWITCH) {
            switch_t* sw = &r->tabMachine[i].donnee.switchs;
            
            // Envoyer des BPDUs sur tous les ports
            for (int port = 0; port < sw->nbPort; port++) {
                envoyerBPDU(sw, port);
            }
        }
    }
    
    // Étape 3: Les switches reçoivent et traitent les BPDUs
    for (int i = 0; i < r->nb_lien; i++) {
        lien l = r->tabLien[i];
        if (l.machine_1.type == TYPE_SWITCH && l.machine_2.type == TYPE_SWITCH) {
            // Simuler l'échange de BPDUs entre switches
            BPDU bpdu1, bpdu2;
            // ... remplir les BPDUs ...
            recevoirBPDU(&l.machine_1.donnee.switchs, &bpdu2, l.machine_1_port);
            recevoirBPDU(&l.machine_2.donnee.switchs, &bpdu1, l.machine_2_port);
        }
    }
    
    // Étape 4: Résolution des BPDUs
    for (int i = 0; i < r->nb_machine; i++) 
    {
        if (r->tabMachine[i].type == TYPE_SWITCH) {
            resoudreBPDU(&r->tabMachine[i].donnee.switchs);
        }
    }
    
    printf("\n=== État final du Spanning Tree ===\n");
    for (int i = 0; i < r->nb_machine; i++) 
    {
        if (r->tabMachine[i].type == TYPE_SWITCH) {
            afficherInfosSTP(&r->tabMachine[i].donnee.switchs);
        }
    }
}

void afficherInfosSTP(switch_t* sw) {
    char mac_str[18];
    char root_mac[18];
    
    ecrireMac(sw->adrMac, mac_str);
    ecrireMac(sw->designated_bridge_id, root_mac);
    
    printf("Switch %s:\n", mac_str);
    printf("  Root Bridge: %s\n", sw->is_root_bridge ? "Oui" : "Non");
    printf("  Designated Bridge ID: %s\n", root_mac);
    printf("  Root Path Cost: %u\n", sw->root_path_cost);
    printf("  Root Port: %d\n", sw->root_port);
}

