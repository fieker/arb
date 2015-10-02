/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2015 Fredrik Johansson

******************************************************************************/

#include "arb_poly.h"

int main()
{
    long iter;
    flint_rand_t state;

    printf("root_bound_fujiwara....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 10000; iter++)
    {
        arb_poly_t a;
        arb_ptr roots;
        arb_t t;
        mag_t mag1, mag2;
        long i, deg, prec;

        prec = 10 + n_randint(state, 400);
        deg = n_randint(state, 10);

        arb_init(t);
        arb_poly_init(a);
        mag_init(mag1);
        mag_init(mag2);
        roots = _arb_vec_init(deg);

        for (i = 0; i < deg; i++)
            arb_randtest(roots + i, state, prec, 1 + n_randint(state, 20));

        arb_poly_product_roots(a, roots, deg, prec);
        arb_randtest(t, state, prec, 1 + n_randint(state, 20));
        _arb_vec_scalar_mul(a->coeffs, a->coeffs, a->length, t, prec);

        arb_poly_root_bound_fujiwara(mag1, a);

        for (i = 0; i < deg; i++)
        {
            arb_get_mag(mag2, roots + i);

            /* arb_get_mag gives an upper bound which due to rounding
               could be larger than mag1, so we pick a slightly
               smaller number */
            mag_mul_ui(mag2, mag2, 10000);
            mag_div_ui(mag2, mag2, 10001);

            if (mag_cmp(mag2, mag1) > 0)
            {
                printf("FAIL\n");
                printf("a = "); arb_poly_printd(a, 15); printf("\n\n");
                printf("root = "); arb_printd(roots + i, 15); printf("\n\n");
                printf("mag1 = "); mag_printd(mag1, 10); printf("\n\n");
                printf("mag2 = "); mag_printd(mag2, 10); printf("\n\n");
                abort();
            }
        }

        _arb_vec_clear(roots, deg);
        arb_clear(t);
        arb_poly_clear(a);
        mag_clear(mag1);
        mag_clear(mag2);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}

