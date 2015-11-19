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

    Copyright (C) 2013 Fredrik Johansson

******************************************************************************/

#include "arb.h"

void
arb_hypot(arb_t z, const arb_t x, const arb_t y, slong prec)
{
    if (arb_is_zero(y))
    {
        arb_abs(z, x);
    }
    else if (arb_is_zero(x))
    {
        arb_abs(z, y);
    }
    else
    {
        arb_t t;
        arb_init(t);
        /* TODO: use arb_fmma */
        arb_mul(t, x, x, prec + 4);
        arb_mul(z, y, y, prec + 4);
        arb_add(t, t, z, prec + 4);
        arb_sqrtpos(z, t, prec);
        arb_clear(t);
    }
}

