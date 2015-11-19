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

#include "fmprb.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("rsqrt....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 100000; iter++)
    {
        fmprb_t a, b, c;
        slong prec = 2 + n_randint(state, 200);

        fmprb_init(a);
        fmprb_init(b);
        fmprb_init(c);

        fmprb_randtest(a, state, 1 + n_randint(state, 200), 10);

        fmprb_rsqrt(b, a, prec);

        fmprb_inv(c, b, prec);
        fmprb_mul(c, c, c, prec);

        if (!fmprb_contains(c, a))
        {
            flint_printf("FAIL: containment\n\n");
            flint_printf("a = "); fmprb_print(a); flint_printf("\n\n");
            flint_printf("b = "); fmprb_print(b); flint_printf("\n\n");
            flint_printf("c = "); fmprb_print(c); flint_printf("\n\n");
            abort();
        }

        fmprb_rsqrt(a, a, prec);

        if (!fmprb_equal(a, b))
        {
            flint_printf("FAIL: aliasing\n\n");
            abort();
        }

        fmprb_clear(a);
        fmprb_clear(b);
        fmprb_clear(c);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}
