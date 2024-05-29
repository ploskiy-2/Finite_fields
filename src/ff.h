#pragma once

#include <stdbool.h>
#include <stdint.h>
                                   
/* Struct for polynomial */
typedef struct 
{
    uint8_t deg; /* degree of the polynomial*/
    uint8_t *coeff; /* big-endian, 3*x^2 + 4x + 1 ---> {1,4,3} */
} poly_t;

/* Struct for finite fields element */
typedef struct {
    uint8_t p; /*char of field*/
    poly_t poly; /*irreducible polynom*/
    uint8_t deg;
    uint8_t *coeff; /* big-endian, 3*x^2 + 4x + 1 ---> {1,4,3} */
} ff_elem;


/* Free allocated memory for polynom and element*/
void poly_free (poly_t *m);
void ff_elem_free (ff_elem *m);

/* Create polynom from array */
poly_t *init_poly_from_array (uint8_t deg, uint8_t *coeff);

/* Return copy polynom*/
poly_t *copy_poly (poly_t *pp);

/* Check equality of two polynoms */
bool poly_equal(poly_t *f, poly_t *g);


/* We want to create element p^n
We need characteristic of field -> p - prime number
We need an irreducible polynomial of degree n  --> irr_p 
We need an arbitrary polynomial of some degree ---> random_p
1) take modulo p ratios random_p
2.1) If the degree random_p is less than irr_p, then random_p is the element of the field p^n
(after taking modulo)
2.2) If degrees of random_p >= degree irr_p, then
random_p  % irr_p --> element of p^n*/
ff_elem *init_ff_elem (poly_t *irr_p, uint8_t p, poly_t *random_p);

/* Modulo all coefficients by modulo p */
void modulo_polynom (poly_t *f, uint8_t p);

/* Remove leading zeroes */
void normalize_polynom (poly_t *f);