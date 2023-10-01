#include <stdlib.h>

#include "Config.h"

type_el make_poison_el()
{
    type_el *x = (type_el *)calloc(sizeof(type_el), sizeof(char));
    for (int i = 0; i < (int)sizeof(type_el); i++) {
        *((char *)x + i) = POISON_BYTE; 
    }
    return *x;
}