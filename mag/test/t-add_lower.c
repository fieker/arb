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

    flint_printf("add_lower....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 100000; iter++)
    {
        fmpr_t x, y, z, z2, w;
        mag_t xb, yb, zb;

        fmpr_init(x);
        fmpr_init(y);
        fmpr_init(z);
        fmpr_init(z2);
        fmpr_init(w);

        mag_init(xb);
        mag_init(yb);
        mag_init(zb);

        mag_randtest_special(xb, state, 100);
        mag_randtest_special(yb, state, 100);

        mag_get_fmpr(x, xb);
        mag_get_fmpr(y, yb);

        fmpr_add(z2, x, y, 100, FMPR_RND_DOWN);

        fmpr_mul_ui(z, z2, 1023, MAG_BITS, FMPR_RND_DOWN);
        fmpr_mul_2exp_si(z, z, -10);

        mag_add_lower(zb, xb, yb);
        mag_get_fmpr(w, zb);

        MAG_CHECK_BITS(xb)
        MAG_CHECK_BITS(yb)
        MAG_CHECK_BITS(zb)

        if (!(fmpr_cmpabs(z, w) <= 0 && fmpr_cmpabs(w, z2) <= 0))
        {
            flint_printf("FAIL\n\n");
            flint_printf("x = "); fmpr_print(x); flint_printf("\n\n");
            flint_printf("y = "); fmpr_print(y); flint_printf("\n\n");
            flint_printf("z = "); fmpr_print(z); flint_printf("\n\n");
            flint_printf("w = "); fmpr_print(w); flint_printf("\n\n");
            abort();
        }

        fmpr_clear(x);
        fmpr_clear(y);
        fmpr_clear(z);
        fmpr_clear(z2);
        fmpr_clear(w);

        mag_clear(xb);
        mag_clear(yb);
        mag_clear(zb);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}

