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

#include "acb_hypgeom.h"

void
acb_hypgeom_chebyshev_t(acb_t res, const acb_t n, const acb_t z, long prec)
{
    acb_t t;

    if (acb_is_int(n) && 
        arf_cmpabs_2exp_si(arb_midref(acb_realref(n)), FLINT_BITS - 1) < 0)
    {
        long k = arf_get_si(arb_midref(acb_realref(n)), ARF_RND_DOWN);
        acb_chebyshev_t_ui(res, FLINT_ABS(k), z, prec);
        return;
    }

    if (acb_is_zero(z))
    {
        acb_mul_2exp_si(res, n, -1);
        acb_cos_pi(res, res, prec);
        return;
    }

    if (acb_is_one(z))
    {
        acb_one(res);
        return;
    }

    acb_init(t);
    acb_set_si(t, -1);

    if (acb_equal(t, z))
    {
        acb_cos_pi(res, n, prec);
    }
    else
    {
        acb_sub_ui(t, z, 1, prec);

        if (arf_cmpabs_2exp_si(arb_midref(acb_realref(t)), -2 - prec / 10) < 0 &&
            arf_cmpabs_2exp_si(arb_midref(acb_imagref(t)), -2 - prec / 10) < 0)
        {
            acb_t a, c;

            acb_init(a);
            acb_init(c);

            acb_neg(a, n);
            acb_one(c);
            acb_mul_2exp_si(c, c, -1);
            acb_neg(t, t);
            acb_mul_2exp_si(t, t, -1);
            acb_hypgeom_2f1(res, a, n, c, t, 0, prec);

            acb_clear(a);
            acb_clear(c);
        }
        else if (arb_is_nonnegative(acb_realref(t)))
        {
            acb_acosh(t, z, prec);
            acb_mul(t, t, n, prec);
            acb_cosh(res, t, prec);
        }
        else
        {
            acb_acos(t, z, prec);
            acb_mul(t, t, n, prec);
            acb_cos(res, t, prec);
        }
    }

    acb_clear(t);
}

