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

#include "fmpr.h"


int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("cmpabs....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 100000; iter++)
    {
        slong bits;
        fmpr_t x, y;
        mpfr_t X, Y;
        int cmp1, cmp2;

        bits = 2 + n_randint(state, 200);

        fmpr_init(x);
        fmpr_init(y);

        mpfr_init2(X, bits);
        mpfr_init2(Y, bits);

        fmpr_randtest_special(x, state, bits, 10);
        fmpr_randtest_special(y, state, bits, 10);

        fmpr_get_mpfr(X, x, MPFR_RNDN);
        fmpr_get_mpfr(Y, y, MPFR_RNDN);

        mpfr_abs(X, X, MPFR_RNDN);
        mpfr_abs(Y, Y, MPFR_RNDN);

        cmp1 = fmpr_cmpabs(x, y);
        cmp2 = mpfr_cmp(X, Y);

        if (cmp1 != cmp2)
        {
            flint_printf("FAIL\n\n");
            flint_printf("x = "); fmpr_print(x); flint_printf("\n\n");
            flint_printf("y = "); fmpr_print(y); flint_printf("\n\n");
            flint_printf("cmp1 = %d, cmp2 = %d\n\n", cmp1, cmp2);
            abort();
        }

        fmpr_clear(x);
        fmpr_clear(y);

        mpfr_clear(X);
        mpfr_clear(Y);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}
