# S21-SAE

## Structure du code

### `reseau.c`
- `initReseau` – Initialise la structure du réseau (allocation mémoire)  
- `deinitReseau` – Libère la mémoire du réseau  
- `affichageReseau` – Affiche le réseau (machines, liens, STP)  
  - `afficheLien` – Affiche tous les liens du réseau  
  - `simulerSTP` – Simule le Spanning Tree Protocol  
    - `electRootBridge` – Élit le root bridge du réseau  
    - `envoyerBPDU` – Envoie des BPDUs sur les ports des switches  
    - `recevoirBPDU` – Reçoit et traite les BPDUs  
    - `resoudreBPDU` – Met à jour l'état STP d'un switch  
    - `afficherInfosSTP` – Affiche les infos STP d'un switch  
- `remplirReseauAvecFichier` – Remplit le réseau à partir d’un fichier de config  
  - `initMachineStation` – Crée une machine de type station  
  - `initMachineSwitch` – Crée une machine de type switch  
  - `ajouterMachine` – Ajoute une machine au réseau  
  - `ajouterLien` – Ajoute un lien au réseau  

### `mac.c`
- `lireMac` – Convertit une chaîne en adresse MAC  
- `ecrireMac` – Convertit une adresse MAC en chaîne lisible  
- `macEquals` – Compare deux adresses MAC  

### `ip.c`
- `lireIp` – Convertit une chaîne en adresse IP  
- `ecrireIp` – Convertit une adresse IP en chaîne lisible  
- `ipEquals` – Compare deux adresses IP  

### `fichierConfiguration.c`
- `afficheLien` – Affiche les liens du réseau  
  - `af_chercheLAutreMachineDuLien` – Cherche l'autre machine d’un lien  
    - `af_afficheLeLien` – Affiche un lien formaté  
- `af_chercheDansLesLiens` – Cherche les liens d'une machine  
- `af_ajustementIndice` – Ajuste l’indice d’une machine pour l'affichage  
- `trouveIndiceFicConf` – Trouve l’indice d’une machine dans le fichier de config  

### `switch.c`
- `initSwitch` – Initialise un switch  
- `deinitSwitch` – Libère la mémoire d’un switch  
- `creerConnexion` – Ajoute une connexion dans la table de commutation  
- `supprimerConnexion_parMac` – Supprime une connexion par MAC  
- `envoyerBPDU` – Envoie un BPDU (STP)  
- `recevoirBPDU` – Reçoit un BPDU (STP)  
- `resoudreBPDU` – Met à jour l’état STP  
- `chercheMacDansTabCommu` – Cherche une MAC dans la table de commutation  

### `table_commutation.c`
- `init_table_commutation` – Initialise la table de commutation  
- `ajouter_entree` – Ajoute une entrée (MAC, port)  
- `rechercher_port` – Recherche un port à partir d’une MAC  
- `afficher_table_commutation` – Affiche la table de commutation  

### `ethernet.c`
- `init_ethernet_frame` – Initialise une trame Ethernet  
- `remplir_trame_ethernet` – Remplit une trame Ethernet  
- `afficher_trame_ethernet` – Affiche une trame Ethernet  

### `main.c`
- `main` – Point d’entrée du programme, lance les tests et l'affichage du réseau  
