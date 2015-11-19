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

#include "arf.h"

int
arf_add_fmpz_2exp_naive(arf_t z, const arf_t x,
    const fmpz_t y, const fmpz_t e, slong prec, arf_rnd_t rnd)
{
    arf_t t;
    int r;
    arf_init(t);
    arf_set_fmpz_2exp(t, y, e);
    r = arf_add(z, x, t, prec, rnd);
    arf_clear(t);
    return r;
}

int main()
{
    slong iter, iter2;
    flint_rand_t state;

    flint_printf("add_fmpz_2exp_fmpz....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 1000; iter++)
    {
        arf_t x, z, v;
        fmpz_t y, e;
        slong prec, r1, r2;
        arf_rnd_t rnd;

        arf_init(x);
        arf_init(z);
        arf_init(v);
        fmpz_init(y);
        fmpz_init(e);

        for (iter2 = 0; iter2 < 100; iter2++)
        {
            arf_randtest_special(x, state, 2000, 10);
            fmpz_randtest(y, state, 2000);
            fmpz_randtest(e, state, 10);
            prec = 2 + n_randint(state, 2000);

            if (n_randint(state, 10) == 0 && fmpz_bits(ARF_EXPREF(x)) < 10)
            {
                prec = ARF_PREC_EXACT;
            }

            switch (n_randint(state, 4))
            {
                case 0:  rnd = ARF_RND_DOWN; break;
                case 1:  rnd = ARF_RND_UP; break;
                case 2:  rnd = ARF_RND_FLOOR; break;
                default: rnd = ARF_RND_CEIL; break;
            }

            switch (n_randint(state, 2))
            {
            case 0:
                r1 = arf_add_fmpz_2exp(z, x, y, e, prec, rnd);
                r2 = arf_add_fmpz_2exp_naive(v, x, y, e, prec, rnd);
                if (!arf_equal(z, v) || r1 != r2)
                {
                    flint_printf("FAIL!\n");
                    flint_printf("prec = %wd, rnd = %d\n\n", prec, rnd);
                    flint_printf("x = "); arf_print(x); flint_printf("\n\n");
                    flint_printf("y = "); fmpz_print(y); flint_printf("\n\n");
                    flint_printf("e = "); fmpz_print(e); flint_printf("\n\n");
                    flint_printf("z = "); arf_print(z); flint_printf("\n\n");
                    flint_printf("v = "); arf_print(v); flint_printf("\n\n");
                    flint_printf("r1 = %wd, r2 = %wd\n", r1, r2);
                    abort();
                }
                break;

            default:
                r2 = arf_add_fmpz_2exp_naive(v, x, y, e, prec, rnd);
                r1 = arf_add_fmpz_2exp(x, x, y, e, prec, rnd);
                if (!arf_equal(x, v) || r1 != r2)
                {
                    flint_printf("FAIL (aliasing)!\n");
                    flint_printf("prec = %wd, rnd = %d\n\n", prec, rnd);
                    flint_printf("x = "); arf_print(x); flint_printf("\n\n");
                    flint_printf("y = "); fmpz_print(y); flint_printf("\n\n");
                    flint_printf("e = "); fmpz_print(e); flint_printf("\n\n");
                    flint_printf("v = "); arf_print(v); flint_printf("\n\n");
                    flint_printf("r1 = %wd, r2 = %wd\n", r1, r2);
                    abort();
                }
                break;
            }
        }

        arf_clear(x);
        arf_clear(z);
        arf_clear(v);
        fmpz_clear(y);
        fmpz_clear(e);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}
