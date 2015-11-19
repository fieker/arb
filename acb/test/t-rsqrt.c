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

    Copyright (C) 2013 Fredrik Johansson

******************************************************************************/

#include "acb.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("rsqrt....");
    fflush(stdout);

    flint_randinit(state);

    /* check (a^(-1/2))^(-2) = a */
    for (iter = 0; iter < 10000; iter++)
    {
        acb_t a, b, c;
        slong prec;

        acb_init(a);
        acb_init(b);
        acb_init(c);

        acb_randtest(a, state, 1 + n_randint(state, 2000), 10);
        acb_randtest(b, state, 1 + n_randint(state, 2000), 10);

        prec = 2 + n_randint(state, 2000);

        acb_rsqrt(b, a, prec);
        acb_inv(c, b, prec);
        acb_mul(c, c, c, prec);

        if (!acb_contains(c, a))
        {
            flint_printf("FAIL: containment\n\n");
            flint_printf("a = "); acb_print(a); flint_printf("\n\n");
            flint_printf("b = "); acb_print(b); flint_printf("\n\n");
            flint_printf("c = "); acb_print(c); flint_printf("\n\n");
            abort();
        }

        acb_rsqrt(a, a, prec);
        if (!acb_equal(a, b))
        {
            flint_printf("FAIL: aliasing\n\n");
            flint_printf("a = "); acb_print(a); flint_printf("\n\n");
            flint_printf("b = "); acb_print(b); flint_printf("\n\n");
            abort();
        }

        acb_clear(a);
        acb_clear(b);
        acb_clear(c);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}

