enum type_machine{
  TYPE_STATION ,
  TYPE_SWITCH 
}; 

union machine {
    struct station station;
    struct sWitch sWitch;
};

struct element_tabMachine{
    type_machine type;
    union machine donnee;
};



#define MAX_MACHINES 100

struct reseau{
    element_tabMachine tabSommet[MAX_MACHINES]; // Définition de la taille du tableau
    int nombreMachines; // Ajout d'un compteur pour le nombre de machines
    // tab[0].type = TYPE_STATION
    // tab[0].adrMac =...
    // tab[0].adrIP=...
    //
    // tab[1].type = TYPE_SWITCH;
    // tab[1].adrMac = ...;
    // tab[1].nbPort = ...;
    // tab[1].priorite = ..;
    // tab[1].tabCommu = .. ;
}; // Ajout d'un point-virgule pour terminer la déclaration de la structure

int getNombreMachine(struct reseau reseau);
int getNombreConnexion(struct reseau reseau);