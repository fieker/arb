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

void
arb_ceil(arb_t z, const arb_t x, slong prec)
{
    if (!arb_is_finite(x))
    {
        arb_indeterminate(z);
    }
    else if (arb_is_exact(x))
    {
        arf_ceil(arb_midref(z), arb_midref(x));
        mag_zero(arb_radref(z));
        arb_set_round(z, z, prec);
    }
    else
    {
        arf_t a, b;
        arf_init(a);
        arf_init(b);

        arb_get_interval_arf(a, b, x, prec);
        arf_ceil(a, a);
        arf_ceil(b, b);
        arb_set_interval_arf(z, a, b, prec);

        arf_clear(a);
        arf_clear(b);
    }
}

