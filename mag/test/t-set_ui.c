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

    Copyright (C) 2014 Fredrik Johansson

******************************************************************************/

#include "mag.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("set_ui....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 100000; iter++)
    {
        fmpr_t a, b, c;
        mag_t m;
        ulong x;

        fmpr_init(a);
        fmpr_init(b);
        fmpr_init(c);
        mag_init(m);

        x = n_randtest(state);

        fmpr_set_ui(a, x);
        mag_set_ui(m, x);

        mag_get_fmpr(b, m);

        fmpr_set(c, a);
        fmpr_mul_ui(c, c, 1025, MAG_BITS, FMPR_RND_UP);
        fmpr_mul_2exp_si(c, c, -10);

        MAG_CHECK_BITS(m)

        if (!(fmpr_cmpabs(a, b) <= 0 && fmpr_cmpabs(b, c) <= 0))
        {
            flint_printf("FAIL\n\n");
            flint_printf("x = %wu\n\n", x);
            flint_printf("a = "); fmpr_print(a); flint_printf("\n\n");
            flint_printf("b = "); fmpr_print(b); flint_printf("\n\n");
            flint_printf("c = "); fmpr_print(c); flint_printf("\n\n");
            abort();
        }

        fmpr_clear(a);
        fmpr_clear(b);
        fmpr_clear(c);
        mag_clear(m);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}

