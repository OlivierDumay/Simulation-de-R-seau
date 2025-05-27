typedef struct {
    int index;
    mac adrMac;
    int port;
}tabCommutation;

struct switch{
    mac adrMac;
    int nbPort;
    int8_t priorite;
    tabCommutation tabCommu;
};

creerConnexion(mac, port);
afficherMAC(mac);
supprimerConnexion(port);
supprimerConnexion(mac);

macExisteDansTable(mac);
portLibre(port);

envoyerBPDU(BPDU, port);
resoudreBPDU();