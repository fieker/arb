/*=============================================================================

    This file is part of acb.

    acb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    acb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with acb; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Fredrik Johansson

******************************************************************************/

#include "acb.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("rising_ui_rs....");
    fflush(stdout);

    flint_randinit(state);

    /* check functional equation */
    for (iter = 0; iter < 1000; iter++)
    {
        acb_t x, xn, y, z;
        ulong n, m, step1, step2, step3;

        acb_init(x);
        acb_init(xn);
        acb_init(y);
        acb_init(z);

        acb_randtest(x, state, 1 + n_randint(state, 4000), 10);
        n = n_randint(state, 80);
        m = n_randint(state, 40);
        acb_add_ui(xn, x, n, 1 + n_randint(state, 4000));

        step1 = n_randint(state, 20);
        step2 = n_randint(state, 20);
        step3 = n_randint(state, 20);

        acb_rising_ui_rs(y, x, n, step1, 2 + n_randint(state, 4000));
        acb_rising_ui_rs(z, xn, m, step2, 2 + n_randint(state, 4000));
        acb_mul(y, y, z, 2 + n_randint(state, 4000));

        acb_rising_ui_rs(z, x, n + m, step3, 2 + n_randint(state, 4000));

        if (!acb_overlaps(y, z))
        {
            flint_printf("FAIL: overlap\n\n");
            flint_printf("n = %wu\n", n);
            flint_printf("m = %wu\n", m);
            flint_printf("x = "); acb_print(x); flint_printf("\n\n");
            flint_printf("xn = "); acb_print(xn); flint_printf("\n\n");
            flint_printf("y = "); acb_print(y); flint_printf("\n\n");
            flint_printf("z = "); acb_print(z); flint_printf("\n\n");
            abort();
        }

        acb_clear(x);
        acb_clear(xn);
        acb_clear(y);
        acb_clear(z);
    }

    /* aliasing of y and x */
    for (iter = 0; iter < 1000; iter++)
    {
        acb_t x, y;
        ulong n;
        slong prec;
        ulong step;

        acb_init(x);
        acb_init(y);

        acb_randtest(x, state, 1 + n_randint(state, 200), 10);
        acb_randtest(y, state, 1 + n_randint(state, 200), 10);
        n = n_randint(state, 100);

        step = n_randint(state, 20);

        prec = 2 + n_randint(state, 4000);
        acb_rising_ui_rs(y, x, n, step, prec);
        acb_rising_ui_rs(x, x, n, step, prec);

        if (!acb_equal(x, y))
        {
            flint_printf("FAIL: aliasing\n\n");
            flint_printf("x = "); acb_print(x); flint_printf("\n\n");
            flint_printf("y = "); acb_print(y); flint_printf("\n\n");
            flint_printf("n = %wu\n", n);
            abort();
        }

        acb_clear(x);
        acb_clear(y);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}
