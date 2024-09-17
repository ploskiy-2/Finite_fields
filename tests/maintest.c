#include "minunit.h"
#include "ff.h"

uint8_t coeff_poly_d2_p2[3] = {1, 1, 1};
struct ff ff_d2_p2 = {.char_p = 2, .deg = 2, .coeff = coeff_poly_d2_p2};

uint8_t coeff_poly_d4_p7[5] = {3, 4, 5, 0, 1};
struct ff ff_d4_p7 = {.char_p = 7, .deg = 4, .coeff = coeff_poly_d4_p7};

uint8_t coeff_poly_d2_p3[3] = {2, 0, 2};
struct ff ff_d2_p3 = {.char_p = 3, .deg = 2, .coeff = coeff_poly_d2_p3};

uint8_t coeff_poly_d5_p2[6] = {1, 0, 1, 0, 0, 1};
struct ff ff_d5_p2 = {.char_p = 2, .deg = 5, .coeff = coeff_poly_d5_p2};

MU_TEST(test_zero_one)
{
    ff_elem_t *zero = ff_get_zero(&ff_d2_p2);
    mu_check(zero->deg == 0);
    mu_check(zero->ff->char_p == 2);
    mu_check(zero->ff->deg == 2);
    for (size_t i = 0; i < zero->ff->deg; ++i)
    {
        mu_check(zero->coeff[i] == 0);
    }

    ff_elem_t *one = ff_get_one(&ff_d4_p7);
    mu_check(one->deg == 0);
    mu_check(one->ff->char_p == 7);
    mu_check(one->ff->deg == 4);
    mu_check(one->coeff[0] == 1);
    for (size_t i = 1; i < one->ff->deg; ++i)
    {
        mu_check(one->coeff[i] == 0);
    }

    ff_elem_free(zero);
    ff_elem_free(one);
}

MU_TEST(test_equal)
{
    ff_elem_t *zero = ff_get_zero(&ff_d2_p2);
    ff_elem_t *one = ff_get_one(&ff_d2_p2);
    ff_elem_t *other_one = ff_get_one(&ff_d4_p7);
    
    mu_check(ff_elem_cmp(zero, one) == -1);
    mu_check(ff_elem_cmp(zero, zero) == 0);
    mu_check(ff_elem_cmp(one, zero) == 1);
    mu_check(ff_elem_cmp(one, other_one) == 0);

    ff_elem_free(zero);
    ff_elem_free(one);
    ff_elem_free(other_one);
}

MU_TEST(test_from_array)
{
    uint8_t a_coeff[5] = {7, 13, 40, 0, 200};
    ff_elem_t *a = ff_elem_from_array(5, a_coeff, &ff_d5_p2);
    mu_check(a->deg == 1);
    mu_check(a->coeff[0] == 1);
    mu_check(a->coeff[1] == 1);
    mu_check(a->coeff[2] == 0);
    mu_check(a->coeff[3] == 0);
    mu_check(a->coeff[4] == 0);


    uint8_t b_coeff[8] = {1, 1, 0, 0, 0, 0, 0, 1};
    ff_elem_t *b = ff_elem_from_array(8, b_coeff, &ff_d5_p2);
    mu_check(b->deg == 4);
    mu_check(b->coeff[0] == 1);
    mu_check(b->coeff[1] == 1);
    mu_check(b->coeff[2] == 1);
    mu_check(b->coeff[3] == 0);
    mu_check(b->coeff[4] == 1);

    ff_elem_free(a);
    ff_elem_free(b);
}

MU_TEST(test_sum)
{
    uint8_t a_coeff[5] = {1, 1, 1, 0, 0};
    ff_elem_t *a = ff_elem_from_array(5, a_coeff, &ff_d5_p2);
    mu_check(a->deg == 2);

    uint8_t b_coeff[5] = {0, 1, 1, 0, 1};
    ff_elem_t *b = ff_elem_from_array(5, b_coeff, &ff_d5_p2);
    mu_check(b->deg == 4);

    ff_elem_t *s1 = ff_sum(a, b);
    mu_check(s1->deg == 4);
    mu_check(s1->coeff[0] == 1);
    mu_check(s1->coeff[1] == 0);
    mu_check(s1->coeff[2] == 0);
    mu_check(s1->coeff[3] == 0);
    mu_check(s1->coeff[4] == 1);

    uint8_t c_coeff[5] = {1, 1, 1, 1, 1};
    ff_elem_t *c = ff_elem_from_array(5, c_coeff, &ff_d5_p2);

    ff_elem_t *s2 = ff_sum(c, c);
    mu_check(s2->deg == 0);
    mu_check(s2->coeff[0] == 0);
    mu_check(s2->coeff[1] == 0);
    mu_check(s2->coeff[2] == 0);
    mu_check(s2->coeff[3] == 0);
    mu_check(s2->coeff[4] == 0);

    ff_elem_free(a);
    ff_elem_free(b);
    ff_elem_free(c);
    ff_elem_free(s1);
    ff_elem_free(s2);
}

MU_TEST(test_sub)
{
    uint8_t a_coeff[3] = {2, 3, 3};
    ff_elem_t *a = ff_elem_from_array(3, a_coeff, &ff_d4_p7);
    mu_check(a->deg == 2);
    mu_check(a->coeff[0] == 2);
    mu_check(a->coeff[1] == 3);
    mu_check(a->coeff[2] == 3);
    mu_check(a->coeff[3] == 0);

    uint8_t b_coeff[5] = {0, 5, 3, 3, 6};
    ff_elem_t *b = ff_elem_from_array(5, b_coeff, &ff_d4_p7);
    mu_check(b->deg == 3);
    mu_check(b->coeff[0] == 3);
    mu_check(b->coeff[1] == 2);
    mu_check(b->coeff[2] == 1);
    mu_check(b->coeff[3] == 3);

    ff_elem_t *s = ff_sub(a, b);
    mu_check(s->deg == 3);
    mu_check(s->coeff[0] == 6);
    mu_check(s->coeff[1] == 1);
    mu_check(s->coeff[2] == 2);
    mu_check(s->coeff[3] == 4);

    ff_elem_free(a);
    ff_elem_free(b);
    ff_elem_free(s);
}

MU_TEST(test_uint8_to_element)
{
    uint8_t expected[8] = {0, 0, 0, 1};
    ff_elem_t *a = uint8_to_ff_elem(8);

    for (size_t i = 0; i < 8; i++)
    {
        mu_check(a->coeff[i] == expected[i]);
    }

    ff_elem_free(a);
}

MU_TEST(test_element_to_uint8)
{
    uint8_t x[8] = {1, 0, 0, 1};
    ff_elem_t *a = ff_elem_from_array(8, x, &ff_d8_p2);

    mu_check(ff_elem_to_uint8(a) == 9);

    ff_elem_free(a);
}

MU_TEST(test_uint16_to_element)
{
    uint8_t expected[16] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 1};
    ff_elem_t *a = uint16_to_ff_elem(515);

    for (size_t i = 0; i < 16; i++)
    {
        mu_check(a->coeff[i] == expected[i]);
    }

    ff_elem_free(a);
}

MU_TEST(test_element_to_uint16)
{
    uint8_t x[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    ff_elem_t *a = ff_elem_from_array(16, x, &ff_d16_p2);

    mu_check(ff_elem_to_uint16(a) == 1023);

    ff_elem_free(a);
}

MU_TEST(test_uint32_to_element)
{
    uint8_t expected[32] = {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1};
    ff_elem_t *a = uint32_to_ff_elem(70432);

    for (size_t i = 0; i < 32; i++)
    {
        mu_check(a->coeff[i] == expected[i]);
    }

    ff_elem_free(a);
}

MU_TEST(test_element_to_uint32)
{
    uint8_t x[32] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    ff_elem_t *a = ff_elem_from_array(32, x, &ff_d32_p2);

    mu_check(ff_elem_to_uint32(a) == 131071);

    ff_elem_free(a);
}

MU_TEST_SUITE(suite_init)
{
    MU_RUN_TEST(test_zero_one);
    MU_RUN_TEST(test_equal);
    MU_RUN_TEST(test_from_array);
    MU_RUN_TEST(test_sum);
    MU_RUN_TEST(test_sub);
    MU_RUN_TEST(test_uint8_to_element);
    MU_RUN_TEST(test_element_to_uint8);
    MU_RUN_TEST(test_uint16_to_element);
    MU_RUN_TEST(test_element_to_uint16);
    MU_RUN_TEST(test_uint32_to_element);
    MU_RUN_TEST(test_element_to_uint32);
}

int main(int argc, char* argv[])
{

    MU_RUN_SUITE(suite_init);
    MU_REPORT();

    return MU_EXIT_CODE;
}