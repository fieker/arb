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

    Copyright (C) 2012 Fredrik Johansson

******************************************************************************/

#include "arb.h"

int main()
{
    long iter;
    flint_rand_t state;

    printf("root....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 100000; iter++)
    {
        arb_t a, b, c;
        ulong k;
        long prec;

        prec = 2 + n_randint(state, 2000);
        k = n_randtest_not_zero(state);

        arb_init(a);
        arb_init(b);
        arb_init(c);

        arb_randtest(a, state, 1 + n_randint(state, 2000), 1 + n_randint(state, 100));
        arb_randtest(b, state, 1 + n_randint(state, 2000), 1 + n_randint(state, 100));

        arb_root(b, a, k, prec);
        arb_pow_ui(c, b, k, prec);

        if (!arb_contains(c, a))
        {
            printf("FAIL: containment\n\n");
            printf("k = %lu\n", k);
            printf("a = "); arb_print(a); printf("\n\n");
            printf("b = "); arb_print(b); printf("\n\n");
            printf("c = "); arb_print(c); printf("\n\n");
            abort();
        }

        arb_root(a, a, k, prec);

        if (!arb_equal(a, b))
        {
            printf("FAIL: aliasing\n\n");
            abort();
        }

        arb_clear(a);
        arb_clear(b);
        arb_clear(c);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}

