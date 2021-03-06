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

#include "arb.h"

int _arf_set_mpn_fixed(arf_t z, mp_srcptr xp, mp_size_t xn, mp_size_t fixn, int negative, long prec);

int main()
{
    long iter;
    flint_rand_t state;

    printf("get_mpn_fixed_mod_log2....");
    fflush(stdout);

    flint_randinit(state);
    /* _flint_rand_init_gmp(state); */

    for (iter = 0; iter < 100000; iter++)
    {
        arf_t x;
        fmpz_t q;
        mp_ptr w;
        arb_t wb, t;
        mp_size_t wn;
        long prec, prec2;
        int success;
        mp_limb_t error;

        prec = 2 + n_randint(state, 10000);
        wn = 1 + n_randint(state, 200);
        prec2 = FLINT_MAX(prec, wn * FLINT_BITS) + 100;

        arf_init(x);
        arb_init(wb);
        arb_init(t);
        fmpz_init(q);
        w = flint_malloc(sizeof(mp_limb_t) * wn);

        arf_randtest(x, state, prec, 14);

        /* this should generate numbers close to multiples of log(2) */
        if (n_randint(state, 4) == 0)
        {
            arb_const_log2(t, prec);
            fmpz_randtest(q, state, 200);
            arb_mul_fmpz(t, t, q, prec);
            arf_add(x, x, arb_midref(t), prec, ARF_RND_DOWN);
        }

        success = _arb_get_mpn_fixed_mod_log2(w, q, &error, x, wn);

        if (success)
        {
            _arf_set_mpn_fixed(arb_midref(wb), w, wn, wn, 0, FLINT_BITS * wn);
            mag_set_ui_2exp_si(arb_radref(wb), error, -FLINT_BITS * wn);

            arb_const_log2(t, prec2);

            arb_mul_fmpz(t, t, q, prec2);
            arb_add(t, t, wb, prec2);

            if (!arb_contains_arf(t, x))
            {
                printf("FAIL (containment)\n");
                printf("x = "); arf_printd(x, 50); printf("\n\n");
                printf("q = "); fmpz_print(q); printf("\n\n");
                printf("w = "); arb_printd(wb, 50); printf("\n\n");
                printf("t = "); arb_printd(t, 50); printf("\n\n");
                abort();
            }

            arb_const_log2(t, prec2);

            if (arf_sgn(arb_midref(wb)) < 0 ||
                arf_cmp(arb_midref(wb), arb_midref(t)) >= 0)
            {
                printf("FAIL (expected 0 <= w < log(2))\n");
                printf("x = "); arf_printd(x, 50); printf("\n\n");
                printf("w = "); arb_printd(wb, 50); printf("\n\n");
                abort();
            }
        }

        flint_free(w);
        fmpz_clear(q);
        arf_clear(x);
        arb_clear(wb);
        arb_clear(t);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}

