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

void
acb_tan(acb_t r, const acb_t z, long prec)
{
    if (arb_is_zero(acb_imagref(z)))
    {
        arb_tan(acb_realref(r), acb_realref(z), prec);
        arb_zero(acb_imagref(r));
    }
    else if (arb_is_zero(acb_realref(z)))
    {
        arb_tanh(acb_imagref(r), acb_imagref(z), prec);
        arb_zero(acb_realref(r));
    }
    else
    {
        acb_t t;
        acb_init(t);

        if (arf_cmpabs_2exp_si(arb_midref(acb_imagref(z)), 0) < 0)
        {
            acb_sin_cos(r, t, z, prec + 4);
            acb_div(r, r, t, prec);
        }
        else
        {
            acb_mul_2exp_si(t, z, 1);

            if (arf_sgn(arb_midref(acb_imagref(z))) > 0)
            {
                acb_mul_onei(t, t);
                acb_exp(t, t, prec + 4);
                acb_add_ui(r, t, 1, prec + 4);
                acb_div(r, t, r, prec + 4);
                acb_mul_2exp_si(r, r, 1);
                acb_sub_ui(r, r, 1, prec);
                acb_div_onei(r, r);
            }
            else
            {
                acb_div_onei(t, t);
                acb_exp(t, t, prec + 4);
                acb_add_ui(r, t, 1, prec + 4);
                acb_div(r, t, r, prec + 4);
                acb_mul_2exp_si(r, r, 1);
                acb_sub_ui(r, r, 1, prec);
                acb_mul_onei(r, r);
            }
        }

        acb_clear(t);
    }
}

