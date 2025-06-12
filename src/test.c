#include "test.h"

bool testEcrireIp ()
{
    ip ip1 = {128,0,0,55};
    char ret[20];
    ecrireIp(ip1, ret);

    return strcmp(ret,"128.0.0.55");
}

bool testEcrireMac()
{
    mac mac1 = {10,20,20,50,50,150};
    char* ret = (char*) malloc(23*sizeof(char));
    ret[0] = '\0';;
    ecrireMac(mac1, ret);
    bool res = strcmp(ret, "0A:14:14:32:32:96");
    free(ret);
    return res;
}