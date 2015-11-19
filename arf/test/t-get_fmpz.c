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


int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("get_fmpz....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 100000; iter++)
    {
        slong bits;
        arf_t x;
        mpfr_t y;
        fmpz_t z, z2;
        mpz_t w;

        bits = 2 + n_randint(state, 1000);

        arf_init(x);
        mpfr_init2(y, bits);
        fmpz_init(z);
        fmpz_init(z2);
        mpz_init(w);

        arf_randtest(x, state, bits, 10);

        arf_get_mpfr(y, x, MPFR_RNDN);

        switch (n_randint(state, 5))
        {
            case 0:
                arf_get_fmpz(z, x, ARF_RND_FLOOR);
                mpfr_get_z(w, y, MPFR_RNDD);
                break;
            case 1:
                arf_get_fmpz(z, x, ARF_RND_CEIL);
                mpfr_get_z(w, y, MPFR_RNDU);
                break;
            case 2:
                arf_get_fmpz(z, x, ARF_RND_DOWN);
                mpfr_get_z(w, y, MPFR_RNDZ);
                break;
            case 3:
                arf_get_fmpz(z, x, ARF_RND_UP);
                mpfr_get_z(w, y, MPFR_RNDA);
                break;
            default:
                arf_get_fmpz(z, x, ARF_RND_NEAR);
                mpfr_get_z(w, y, MPFR_RNDN);
                break;
        }

        fmpz_set_mpz(z2, w);

        if (!fmpz_equal(z, z2))
        {
            flint_printf("FAIL\n\n");
            flint_printf("x = "); arf_print(x); flint_printf("\n\n");
            flint_printf("z = "); fmpz_print(z); flint_printf("\n\n");
            flint_printf("z2 = "); fmpz_print(z2); flint_printf("\n\n");
            abort();
        }

        arf_clear(x);
        mpfr_clear(y);
        fmpz_clear(z);
        fmpz_clear(z2);
        mpz_clear(w);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}
