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

    Copyright (C) 2015 Arb authors

******************************************************************************/

#include "arb.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("sinc....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 10000; iter++)
    {
        arb_t x, a;
        slong prec, mag_bits;

        prec = 2 + n_randint(state, 500);
        mag_bits = 6 + n_randint(state, 500);

        arb_init(x);
        arb_randtest(x, state, 1 + n_randint(state, prec), mag_bits);

        arb_init(a);
        arb_sinc(a, x, prec);

        /* sinc(x) in [-2, 2] */
        {
            arb_t b;
            arb_init(b);
            arb_zero(b);
            mag_one(arb_radref(b));
            mag_mul_2exp_si(arb_radref(b), arb_radref(b), 1);

            if (!arb_contains(b, a))
            {
                flint_printf("FAIL: containment\n\n");
                flint_printf("x = "); arb_print(x); flint_printf("\n\n");
                flint_printf("a = "); arb_print(a); flint_printf("\n\n");
                flint_printf("b = "); arb_print(b); flint_printf("\n\n");
                abort();
            }

            arb_clear(b);
        }

        /* sinc(x) * x = sin(x) */
        {
            arb_t b, c;
            arb_init(b);
            arb_init(c);

            arb_mul(b, a, x, prec);
            arb_sin(c, x, prec);

            if (!arb_overlaps(b, c))
            {
                flint_printf("FAIL: overlap (sin)\n\n");
                flint_printf("x = "); arb_print(x); flint_printf("\n\n");
                flint_printf("b = "); arb_print(b); flint_printf("\n\n");
                flint_printf("c = "); arb_print(c); flint_printf("\n\n");
                abort();
            }

            arb_clear(b);
            arb_clear(c);
        }

        /* aliasing */
        {
            arb_t b;
            arb_init(b);
            arb_set(b, x);
            arb_sinc(b, b, prec);
            if (!arb_equal(a, b))
            {
                flint_printf("FAIL: aliasing\n\n");
                abort();
            }
            arb_clear(b);
        }

        arb_clear(x);
        arb_clear(a);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}
