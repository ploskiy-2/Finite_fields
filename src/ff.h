#pragma once

#include <stdbool.h>
#include <stdint.h>
                                   
/* Structure of the finite field */
typedef struct ff
{   
    uint8_t char_p; /* Characteristic of the field */
    uint8_t deg;    /* Degree of the irreducible polynomial */
    uint8_t *coeff; /* Coeff of the irreducible polynomial */
} ff_t;

/* Structure of the element of the finite field */
typedef struct ff_elem
{
    ff_t *ff;       /* Finite field */
    uint8_t deg;    /* Degree of the polynomial in the finite field */
    uint8_t *coeff; /* Coeff of the polynomial in the finite field */
} ff_elem_t;

/* Particular fields for task*/
extern ff_t ff_d8_p2;
extern ff_t ff_d16_p2;
extern ff_t ff_d32_p2;

/* Free allocated memory for element*/
void ff_elem_free (ff_elem_t *m);

/* Compare two elements */
int ff_elem_cmp(ff_elem_t *a, ff_elem_t *b);

/* To get inverse element*/
ff_elem_t *inverse_ff_elem(ff_elem_t *a);

/* Create element of the field from array */
ff_elem_t *ff_elem_from_array(size_t length, uint8_t *coeff, ff_t *ff);

/* To get neutral element of the field */
ff_elem_t *ff_get_zero(ff_t *ff);

/* To get neutral element of multiply */
ff_elem_t *ff_get_one(ff_t *ff);

/* Sum of two finite field's elements */
ff_elem_t *ff_sum(ff_elem_t *a, ff_elem_t *b);

/* To get negative finite field's element */
ff_elem_t *negative_ff_elem(ff_elem_t *a);

/* Sub of two finite field's elements */
ff_elem_t *ff_sub(ff_elem_t *a, ff_elem_t *b);

/* Mult of two finite field's elements */
ff_elem_t *ff_multiply(ff_elem_t *a, ff_elem_t *b);

/* Div of two finite field's elements */
ff_elem_t *ff_divide(ff_elem_t *a, ff_elem_t *b);