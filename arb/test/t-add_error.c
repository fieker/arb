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

    Copyright (C) 2012-2015 Fredrik Johansson

******************************************************************************/

#include "arb.h"

int main()
{
    long iter;
    flint_rand_t state;

    printf("add_error....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 10000; iter++)
    {
        arb_t a, b, c;
        arf_t m, r;

        arb_init(a);
        arb_init(b);
        arb_init(c);
        arf_init(m);
        arf_init(r);

        arb_randtest_special(a, state, 1 + n_randint(state, 2000), 10);
        arb_randtest_special(b, state, 1 + n_randint(state, 2000), 10);
        arb_randtest_special(c, state, 1 + n_randint(state, 2000), 10);
        arf_randtest_special(m, state, 1 + n_randint(state, 2000), 10);
        arf_randtest_special(r, state, 1 + n_randint(state, 2000), 10);

        /* c = a plus error bounds */
        arb_set(c, a);
        arf_set(arb_midref(b), m);
        arf_get_mag(arb_radref(b), r);
        arb_add_error(c, b);

        /* b = a + random point */
        arb_set(b, a);

        if (n_randint(state, 2))
            arf_add(arb_midref(b), arb_midref(b), m, ARF_PREC_EXACT, ARF_RND_DOWN);
        else
            arf_sub(arb_midref(b), arb_midref(b), m, ARF_PREC_EXACT, ARF_RND_DOWN);

        if (n_randint(state, 2))
            arf_add(arb_midref(b), arb_midref(b), r, ARF_PREC_EXACT, ARF_RND_DOWN);
        else
            arf_sub(arb_midref(b), arb_midref(b), r, ARF_PREC_EXACT, ARF_RND_DOWN);

        /* should this be done differently? */
        if (arf_is_nan(arb_midref(b)))
            arf_zero(arb_midref(b));

        if (!arb_contains(c, b))
        {
            printf("FAIL (arb_add_error)\n\n");
            printf("a = "); arb_printn(a, 50, 0); printf("\n\n");
            printf("b = "); arb_printn(b, 50, 0); printf("\n\n");
            printf("c = "); arb_printn(c, 50, 0); printf("\n\n");
            abort();
        }

        arb_clear(a);
        arb_clear(b);
        arb_clear(c);
        arf_clear(m);
        arf_clear(r);
    }

    for (iter = 0; iter < 10000; iter++)
    {
        arb_t a, b, c;
        arf_t m;

        arb_init(a);
        arb_init(b);
        arb_init(c);
        arf_init(m);

        arb_randtest_special(a, state, 1 + n_randint(state, 2000), 10);
        arb_randtest_special(b, state, 1 + n_randint(state, 2000), 10);
        arb_randtest_special(c, state, 1 + n_randint(state, 2000), 10);
        arf_randtest_special(m, state, 1 + n_randint(state, 2000), 10);

        /* c = a plus error bounds */
        arb_set(c, a);
        arb_add_error_arf(c, m);

        /* b = a + random point */
        arb_set(b, a);

        if (n_randint(state, 2))
            arf_add(arb_midref(b), arb_midref(b), m, ARF_PREC_EXACT, ARF_RND_DOWN);
        else
            arf_sub(arb_midref(b), arb_midref(b), m, ARF_PREC_EXACT, ARF_RND_DOWN);

        /* should this be done differently? */
        if (arf_is_nan(arb_midref(b)))
            arf_zero(arb_midref(b));

        if (!arb_contains(c, b))
        {
            printf("FAIL (arb_add_error_arf)\n\n");
            printf("a = "); arb_printn(a, 50, 0); printf("\n\n");
            printf("b = "); arb_printn(b, 50, 0); printf("\n\n");
            printf("c = "); arb_printn(c, 50, 0); printf("\n\n");
            abort();
        }

        arb_clear(a);
        arb_clear(b);
        arb_clear(c);
        arf_clear(m);
    }

    for (iter = 0; iter < 10000; iter++)
    {
        arb_t a, b, c;
        arf_t t;
        mag_t r;

        arb_init(a);
        arb_init(b);
        arb_init(c);
        mag_init(r);
        arf_init(t);

        arb_randtest_special(a, state, 1 + n_randint(state, 2000), 10);
        arb_randtest_special(b, state, 1 + n_randint(state, 2000), 10);
        mag_randtest(r, state, 10);

        /* c = a plus error bounds */
        arb_set(c, a);
        arb_add_error_mag(c, r);

        /* b = a + random point */
        arb_set(b, a);
        arf_set_mag(t, r);
        if (n_randint(state, 2))
            arf_add(arb_midref(b), arb_midref(b), t, ARF_PREC_EXACT, ARF_RND_DOWN);
        else
            arf_sub(arb_midref(b), arb_midref(b), t, ARF_PREC_EXACT, ARF_RND_DOWN);

        /* should this be done differently? */
        if (arf_is_nan(arb_midref(b)))
            arf_zero(arb_midref(b));

        if (!arb_contains(c, b))
        {
            printf("FAIL (arb_add_error_mag)\n\n");
            printf("a = "); arb_printn(a, 50, 0); printf("\n\n");
            printf("b = "); arb_printn(b, 50, 0); printf("\n\n");
            printf("c = "); arb_printn(c, 50, 0); printf("\n\n");
            abort();
        }

        arb_clear(a);
        arb_clear(b);
        arb_clear(c);
        mag_clear(r);
        arf_clear(t);
    }

    for (iter = 0; iter < 10000; iter++)
    {
        arb_t a, b, c;
        arf_t t;
        long e;

        arb_init(a);
        arb_init(b);
        arb_init(c);
        arf_init(t);

        arb_randtest_special(a, state, 1 + n_randint(state, 2000), 10);
        arb_randtest_special(b, state, 1 + n_randint(state, 2000), 10);
        e = n_randint(state, 10) - 10;

        /* c = a plus error bounds */
        arb_set(c, a);
        arb_add_error_2exp_si(c, e);

        /* b = a + random point */
        arb_set(b, a);
        arf_one(t);
        arf_mul_2exp_si(t, t, e);
        if (n_randint(state, 2))
            arf_add(arb_midref(b), arb_midref(b), t, ARF_PREC_EXACT, ARF_RND_DOWN);
        else
            arf_sub(arb_midref(b), arb_midref(b), t, ARF_PREC_EXACT, ARF_RND_DOWN);

        /* should this be done differently? */
        if (arf_is_nan(arb_midref(b)))
            arf_zero(arb_midref(b));

        if (!arb_contains(c, b))
        {
            printf("FAIL (arb_add_error_2exp_si)\n\n");
            printf("a = "); arb_printn(a, 50, 0); printf("\n\n");
            printf("b = "); arb_printn(b, 50, 0); printf("\n\n");
            printf("c = "); arb_printn(c, 50, 0); printf("\n\n");
            abort();
        }

        arb_clear(a);
        arb_clear(b);
        arb_clear(c);
        arf_clear(t);
    }

    for (iter = 0; iter < 10000; iter++)
    {
        arb_t a, b, c;
        arf_t t;
        fmpz_t e;

        arb_init(a);
        arb_init(b);
        arb_init(c);
        arf_init(t);
        fmpz_init(e);

        arb_randtest_special(a, state, 1 + n_randint(state, 2000), 10);
        arb_randtest_special(b, state, 1 + n_randint(state, 2000), 10);
        fmpz_randtest(e, state, 10);

        /* c = a plus error bounds */
        arb_set(c, a);
        arb_add_error_2exp_fmpz(c, e);

        /* b = a + random point */
        arb_set(b, a);
        arf_one(t);
        arf_mul_2exp_fmpz(t, t, e);
        if (n_randint(state, 2))
            arf_add(arb_midref(b), arb_midref(b), t, ARF_PREC_EXACT, ARF_RND_DOWN);
        else
            arf_sub(arb_midref(b), arb_midref(b), t, ARF_PREC_EXACT, ARF_RND_DOWN);

        /* should this be done differently? */
        if (arf_is_nan(arb_midref(b)))
            arf_zero(arb_midref(b));

        if (!arb_contains(c, b))
        {
            printf("FAIL (arb_add_error_2exp_fmpz)\n\n");
            printf("a = "); arb_printn(a, 50, 0); printf("\n\n");
            printf("b = "); arb_printn(b, 50, 0); printf("\n\n");
            printf("c = "); arb_printn(c, 50, 0); printf("\n\n");
            abort();
        }

        arb_clear(a);
        arb_clear(b);
        arb_clear(c);
        arf_clear(t);
        fmpz_clear(e);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}
