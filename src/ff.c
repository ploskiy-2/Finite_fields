#include <stdlib.h>
#include <string.h>
#include "ff.h"

/* Inverse and complement element for a over F_p */
static uint8_t inverse_elem (uint8_t a, uint8_t p);
static uint8_t complement_elem (uint8_t a, uint8_t p);
/* Modulo all coefficients by modulo p */
static void modulo_polynom (poly_t *f, uint8_t p);
/* Remove leading zeroes */
static void normalize_polynom (poly_t *f);

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

poly_t *copy_poly (poly_t *pp)
{
    if (!pp)
    {
        return NULL;
    }
    poly_t *copy_pp = malloc(sizeof(copy_pp));
    if (!copy_pp)
    {
        return NULL;
    }
    copy_pp->char_p = pp->char_p;
    copy_pp->deg = pp->deg;
    uint8_t *tmp = calloc(pp->deg + 1, sizeof(*pp->coeff));
    if (!tmp)
    {
        poly_free(copy_pp);
        return NULL;
    } 
    memcpy(tmp, pp->coeff, (pp->deg + 1) * sizeof(*pp->coeff));
    copy_pp->coeff = tmp;
    return copy_pp;
}

bool poly_equal (poly_t *f, poly_t *g)
{
    if (f->deg != g->deg)
    {
        return false;
    }
    if (f->char_p != g->char_p)
    {
        return false;
    }
    if (memcmp(f->coeff, g->coeff, (f->deg + 1) * sizeof(*f->coeff)))
    {
        return false;
    }
    return true;
}

ff_elem *init_ff_elem (poly_t *irr_p, uint8_t p, poly_t *random_p)
{
    if (!irr_p || !random_p)
    {
        return NULL;
    }
    ff_elem *f = malloc(sizeof(*f));
    if (!f)
    {
        return NULL;
    }
    f->p = p;
    f->irr_poly = irr_p;

    if (random_p->deg < irr_p->deg)
    {
        poly_t *c_p = copy_poly(random_p);
        modulo_polynom(c_p, p);
        f->ff_p = c_p;
        return f;
    }

    uint8_t *tmp = calloc(random_p->deg + 1, sizeof(*random_p->coeff));
    if (!tmp)
    {
        ff_elem_free(f);
        return NULL;
    }
    memcpy(tmp, random_p->coeff, sizeof(*random_p->coeff) * (random_p->deg + 1));
    f->ff_p->deg = irr_p->deg - 1;

    uint8_t n = random_p->deg;
    uint8_t m = irr_p->deg;

    uint8_t *v = irr_p->coeff;

    uint8_t q;
    uint8_t w;
    
    for (size_t k = (n - m) + 1; k > 0; --k) 
    {
        q = tmp[(k - 1) + m] * inverse_elem(v[m], p);
        for (size_t i = m + (k - 1) + 1; i > (k - 1); --i) 
        {
            w = (q * v[(i - 1) - (k - 1)]) % p;
            w = complement_elem(w, p);
            tmp[i - 1] = (tmp[i - 1] + w) % p;
        }
    }
    f->ff_p->coeff = tmp;
    normalize_polynom(f->ff_p);
    return f;

}

static void modulo_polynom (poly_t *f, uint8_t p)
{
    if (!f)
    {
        return ;
    }
    for (size_t i=0; i<=f->deg; i++)
    {
        f->coeff[i] %= p;
    }
    normalize_polynom(f);
}

static void normalize_polynom (poly_t *f)
{
    if (!f)
    {
        return ;
    }
    while ((f->deg > 0) && (f->coeff[f->deg] == 0))
    {
        f->deg -= 1;
    }
}