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

    Copyright (C) 2015 Fredrik Johansson

******************************************************************************/

#include "acb.h"

int main()
{
    long iter;
    flint_rand_t state;

    printf("log_sin_pi....");
    fflush(stdout);

    flint_randinit(state);

    /* check functional equation S(s+1) = S(s) + log(-s) - log(s) */
    for (iter = 0; iter < 10000; iter++)
    {
        acb_t s, s1, r, r1, t;
        long prec;

        acb_init(s);
        acb_init(s1);
        acb_init(r);
        acb_init(r1);
        acb_init(t);

        prec = 2 + n_randint(state, 500);
        acb_randtest(s, state, 1 + n_randint(state, 500), 1 + n_randint(state, 10));
        acb_randtest(r, state, 1 + n_randint(state, 500), 1 + n_randint(state, 10));
        acb_randtest(r1, state, 1 + n_randint(state, 500), 1 + n_randint(state, 10));

        acb_log_sin_pi(r, s, prec);

        acb_add_ui(s1, s, 1, prec);

        if (n_randint(state, 4) == 0)
        {
            acb_randtest(t, state, 1 + n_randint(state, 1000), 1 + n_randint(state, 10));
            acb_add(s1, s1, t, prec);
            acb_sub(s1, s1, t, prec);
        }

        acb_log_sin_pi(r1, s1, prec);

        acb_log(t, s, prec);
        acb_sub(r, r, t, prec);
        acb_neg(t, s);
        acb_log(t, t, prec);
        acb_add(r, r, t, prec);

        if (!acb_overlaps(r, r1))
        {
            printf("FAIL: overlap\n\n");
            printf("s  = "); acb_printd(s, 30); printf("\n\n");
            printf("s1 = "); acb_printd(s1, 30); printf("\n\n");
            printf("r  = "); acb_printd(r, 30); printf("\n\n");
            printf("r1 = "); acb_printd(r1, 30); printf("\n\n");
            abort();
        }

        acb_clear(s);
        acb_clear(s1);
        acb_clear(r);
        acb_clear(r1);
        acb_clear(t);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}

