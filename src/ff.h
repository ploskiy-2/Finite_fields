#pragma once

#include <stdbool.h>
#include <stdint.h>
                                   
/* Struct for polynomial */
typedef struct 
{
    uint8_t deg; /* degree of the polynomial*/
    uint8_t *coeff; /* big-endian, 3*x^2 + 4x + 1 ---> {1,4,3} */
    uint8_t p; /*char of field*/
} poly_t;

/* Struct for finite fields element */
typedef struct {
    poly_t poly; 
    uint8_t deg;
    uint8_t *coeff; 
} ff_elem;


/* Free allocated memory for polynom and element*/
void poly_free (poly_t *m);
void ff_elem_free (ff_elem *m);

/* Create polynom from array */
poly_t *init_poly_from_array (uint8_t deg, uint8_t *coeff);

/* Return copy polynom*/
poly_t *copy_poly (poly_t *pp);

bool poly_equal(poly_t *f, poly_t *g);