#include <stdlib.h>
#include <string.h>
#include "ff.h"

/* Inverse and complement element for a over F_p */
static uint8_t inverse_elem (uint8_t a, uint8_t p);
static uint8_t complement_elem (uint8_t a, uint8_t p);

static uint8_t complement_elem (uint8_t a, uint8_t p)
{
    return (p - a) % p;
}

static uint8_t inverse_elem (uint8_t a, uint8_t p)
{
    for (uint8_t x = 1; x < p; x++)
    {
        if ((a * x) % p == 0)
        {
            return x;
        }
    }
    return 1;
}

static void modulo_poly(uint8_t length, uint8_t *coeff, ff_t *ff)
{   
    if (!ff || !coeff)
    {
        return;
    }

    if (length < ff->deg) {
        return;
    }
    for (size_t k = (length - 1 - ff->deg) + 1; k > 0; k--)
    {   
        uint8_t q = coeff[(k - 1) + ff->deg] * inverse_elem(ff->coeff[ff->deg], ff->char_p);
        for (size_t j = ff->deg + (k - 1) + 1; j > (k - 1); j--)
        {
            uint8_t new_value = (q * ff->coeff[(j - 1) - (k - 1)]) % ff->char_p;
            new_value = complement_elem(new_value, ff->char_p);
            coeff[j - 1] = (coeff[j - 1] + new_value) % ff->char_p;
        }
    }
    return;
}

static uint8_t get_deg(size_t length, uint8_t *coeff)
{
    uint8_t deg = length - 1;
    while ((deg > 0) && (coeff[deg] == 0))
    {
        deg -= 1;
    }
    return deg;
}

void ff_elem_free (ff_elem_t *m)
{
    if (m)
    {
        free(m->coeff);
        free(m);
    }
    return ;
}

ff_elem_t *ff_get_zero(ff_t *ff)
{
    if (!ff)
    {
        return NULL;
    }
    ff_elem_t *zero = malloc(sizeof(*zero));
    if (!zero)
    {
        return NULL;
    }
    zero->ff = ff;
    zero->deg = 0;
    zero->coeff = calloc(ff->deg, sizeof(*zero->coeff));
    if (!zero->coeff)
    {
        free(zero);
        return NULL;
    }
    return zero;
}

ff_elem_t *ff_get_one(ff_t *ff)
{
    if (!ff)
    {
        return NULL;
    }
    ff_elem_t *one = ff_get_zero(ff);
    if (!one)
    {
        return NULL;
    }
    one->coeff[0] = 1;
    return one;
}

ff_elem_t *init_ff_elem_from_array (size_t length, uint8_t *coeff, ff_t *ff)
{
    if (!coeff || !ff)
    {
        return NULL;
    }
    ff_elem_t *f = malloc(sizeof(*f));
    if (!f)
    {
        return NULL;
    }
    f->ff = ff;
    f->coeff = calloc(ff->deg, sizeof(uint8_t));
    if (!f->coeff)
    {
        ff_elem_free(f);
        return NULL;
    }

    for (size_t i = 0; i < length; i++)
    {
        coeff[i] %= ff->char_p;
    }

    size_t deg = get_deg(length, coeff);
    
    modulo_poly(deg + 1, coeff, ff);
    deg = get_deg(deg + 1, coeff);
    
    memcpy(f->coeff, coeff, sizeof(uint8_t) * (deg + 1));
    f->deg = deg;
    return f;
}
