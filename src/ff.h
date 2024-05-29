#pragma once

#include <stdbool.h>
#include <stdint.h>
                                   
/**/
typedef struct 
{
    uint8_t deg; /* degree of the polynomial*/
    uint8_t *coeff; /* little-endian, 3*x^2 + 4x + 1 ---> {1,4,3} */
    uint8_t p; /*char of field*/
} poly_t;