#pragma once

#include <stdbool.h>
#include <stdint.h>
                                   
/* Struct for polynomial */
typedef struct 
{
    uint8_t char_p; /* char of field*/
    uint8_t deg; /* degree of the polynomial*/
    uint8_t *coeff; /* little-endian, 3*x^2 + 4x + 1 ---> {1,4,3} */
} poly_t;

/* Struct for finite fields element */
typedef struct {
    uint8_t p; /*char of field*/
    poly_t *irr_poly; /*irreducible polynom*/
    poly_t *ff_p; /*It is a polynomial over the field p^n*/
} ff_elem;


/* Free allocated memory for polynom and element*/
void poly_free (poly_t *m);
void ff_elem_free (ff_elem *m);

/* Create polynom from array */
poly_t *init_poly_from_array (uint8_t deg, uint8_t *coeff, uint8_t p);

/* Return copy polynom*/
poly_t *copy_poly (poly_t *pp);

/* Check equality of two polynoms */
bool poly_equal(poly_t *f, poly_t *g);


/* We want to create element p^n
We need characteristic of field -> p - prime number
We need an irreducible polynomial of degree n over f_p --> irr_p 
We need an arbitrary polynomial of some degree ---> random_p
1) take modulo p ratios random_p
2.1) If the degree random_p is less than irr_p, then random_p is the element of the field p^n
(after taking modulo)
2.2) If degrees of random_p >= degree irr_p, then
random_p  % irr_p --> element of p^n*/
ff_elem *init_ff_elem (poly_t *irr_p, uint8_t p, poly_t *random_p);