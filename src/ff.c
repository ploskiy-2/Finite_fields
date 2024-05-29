#include <stdlib.h>
#include <string.h>
#include "ff.h"

void poly_free (poly_t *m)
{
    if (m)
    {
        free(m->coeff);
        free(m);
    }
    return ;
}

void ff_elem_free (ff_elem *m)
{
    if (m)
    {
        free(m->coeff);
        free(m);
    }
    return ;
}

poly_t *init_poly_from_array (uint8_t deg, uint8_t *coeff)
{
    if (!coeff)
    {
        return NULL;
    }
    poly_t *poly = malloc(sizeof(*poly));
    if (!poly)
    {
        return NULL;
    }
    uint8_t *tmp = calloc(deg+1, sizeof(*coeff));
    if (!tmp)
    {
        poly_free(poly);
        return NULL;
    }
    poly->deg = deg;
    memcpy(tmp, coeff, sizeof(*coeff) * (deg + 1));
    poly->coeff = tmp;
    poly->p = 1;
    
    return poly;

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
    
    copy_pp->p = pp->p;
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
    if (f->p != g->p){
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

}

void modulo_polynom (poly_t *f, uint8_t p)
{
    if (!f)
    {
        return NULL;
    }
    for (size_t i=0; i<=f->deg; i++)
    {
        f->coeff[i] %= p;
    }
    normalize_polynom(f);
}

void normalize_polynom (poly_t *f)
{
    if (!f)
    {
        return NULL;
    }
    while ((f->deg > 0) && (f->coeff[f->deg] == 0))
    {
        f->deg -= 1;
    }
}