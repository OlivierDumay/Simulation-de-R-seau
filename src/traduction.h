#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char * uint8versStringDecimal (uint8_t octet);
void uint8versStringHexadecimal (uint8_t octet, char buffer[3]);
void extraireChaine(const char* chaine, char separateur, char** avant, char** apres);