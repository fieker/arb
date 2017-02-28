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
acb_hypgeom_legendre_p(acb_t res, const acb_t n, const acb_t m,
    const acb_t z, int type, slong prec)
{
    acb_t a, b, c, w;

    if (!acb_is_finite(z))
    {
        acb_indeterminate(res);
        return;
    }

    if (acb_is_int(n) && acb_is_int(m) && arb_is_nonnegative(acb_realref(n))
        && arb_is_nonnegative(acb_realref(m)) && type == 0)
    {
        arf_srcptr nn = arb_midref(acb_realref(n));
        arf_srcptr mm = arb_midref(acb_realref(m));

        if (arf_cmpabs(mm, nn) > 0)
        {
            acb_zero(res);
            return;
        }

        if (arf_cmpabs_2exp_si(nn, FLINT_BITS - 1) < 0 && 
            arf_cmpabs_2exp_si(mm, FLINT_BITS - 1) < 0)
        {
            slong nnn, mmm;

            nnn = arf_get_si(nn, ARF_RND_DOWN);
            mmm = arf_get_si(mm, ARF_RND_DOWN);

            /* we will probably lose all accuracy... */
            if (nnn - mmm > 2 * prec)
            {
                acb_indeterminate(res);
            }  /* hypergeometric series is faster at high precision, but avoid at 1 */
            else if (prec < 500 + nnn * 10.0 || (nnn - mmm) < 10 ||
                (arb_contains_si(acb_realref(z), 1) &&
                 arb_contains_zero(acb_imagref(z))))
            {
                if (mmm == 0)
                {
                    acb_hypgeom_legendre_p_uiui_rec(res, nnn, mmm, z, prec);
                }
                else
                {
                    acb_init(a);
                    acb_init(b);
                    acb_mul(a, z, z, prec);
                    acb_sub_ui(a, a, 1, prec);
                    acb_neg(a, a);
                    acb_mul_2exp_si(b, m, -1);
                    acb_pow(a, a, b, prec);
                    acb_hypgeom_legendre_p_uiui_rec(res, nnn, mmm, z, prec);
                    acb_mul(res, res, a, prec);
                    acb_clear(a);
                    acb_clear(b);
                }

                return;
            }
        }
    }

    acb_init(a);
    acb_init(b);
    acb_init(c);
    acb_init(w);

    acb_neg(a, n);
    acb_add_ui(b, n, 1, prec);

    acb_sub_ui(c, m, 1, prec);
    acb_neg(c, c);

    acb_sub_ui(w, z, 1, prec);
    acb_neg(w, w);
    acb_mul_2exp_si(w, w, -1);

    acb_hypgeom_2f1(w, a, b, c, w, 1, prec);

    if (!acb_is_zero(m))
    {
        acb_add_ui(a, z, 1, prec);
        acb_sub_ui(b, z, 1, prec);

        if (type == 0)
        {
            acb_neg(b, b);
        }
        else if (type != 1)
        {
            flint_printf("unsupported 'type' %d for legendre p\n", type);
            flint_abort();
        }

        acb_mul_2exp_si(c, m, -1);
        acb_pow(a, a, c, prec);
        acb_neg(c, c);
        acb_pow(b, b, c, prec);
        acb_mul(w, w, a, prec);
        acb_mul(w, w, b, prec);
    }

    acb_set(res, w);

    acb_clear(a);
    acb_clear(b);
    acb_clear(c);
    acb_clear(w);
}

