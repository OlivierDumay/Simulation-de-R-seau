struct tabCommutation{
    int index;
    mac adrMac;
    int port;
};

struct switch{
    mac adrMac;
    int nbPort;
    int8_t priorite;
    tabCommutation tabCommu;
};

creerConnexion(mac, port);
supprimerConnexion(port);
supprimerConnexion(mac);

macExisteDansTable(mac);
portLibre(port);

envoyerBPDU(BPDU, port);
resoudreBPDU();