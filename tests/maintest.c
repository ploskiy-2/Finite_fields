#include "minunit.h"
#include "ff.h"

MU_TEST(test_init_poly)
{
    /*1 + 2x + 3*x^2 */
    uint8_t c_f1[3] = {1,2,3};
    poly_t *f = init_poly_from_array(2, c_f1,5);


    uint8_t c_f2[3] = {1,2,3};
    poly_t *g = init_poly_from_array(2, c_f2,4);
   

    /* 1 + x + x^2 + x^3*/
    uint8_t c_f3[4] = {1,1,1,1};
    poly_t *h = init_poly_from_array(3, c_f3,2);
    

    mu_assert_int_eq(f->deg, g->deg);
    mu_assert_int_eq(f->deg, 2);
    mu_assert_int_eq(h->deg, 3);
    
    mu_check(poly_equal(f,f));
    mu_check(!poly_equal(f,g));
    mu_check(!poly_equal(f,h));

    poly_free(f);
    poly_free(g);
    poly_free(h);
}

MU_TEST_SUITE(suite_init)
{
    MU_RUN_TEST(test_init_poly);
}

int main(int argc, char* argv[])
{

    MU_RUN_SUITE(suite_init);
    MU_REPORT();

    return MU_EXIT_CODE;
}