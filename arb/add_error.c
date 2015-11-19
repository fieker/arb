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

void
arb_add_error_arf(arb_t x, const arf_t err)
{
    mag_t t;

    if (arf_is_zero(err))
        return;

    if (mag_is_zero(arb_radref(x)))
    {
        arf_get_mag(arb_radref(x), err);
        return;
    }

    mag_init(t);
    arf_get_mag(t, err);
    mag_add(arb_radref(x), arb_radref(x), t);
    mag_clear(t);
}

void
arb_add_error_2exp_si(arb_t x, slong err)
{
    fmpz_t t;

    if (mag_is_zero(arb_radref(x)))
    {
        mag_one(arb_radref(x));
        mag_mul_2exp_si(arb_radref(x), arb_radref(x), err);
        return;
    }

    fmpz_init(t);
    fmpz_set_si(t, err);
    mag_add_2exp_fmpz(arb_radref(x), arb_radref(x), t);
    fmpz_clear(t);
}

void
arb_add_error_2exp_fmpz(arb_t x, const fmpz_t err)
{
    if (mag_is_zero(arb_radref(x)))
    {
        mag_one(arb_radref(x));
        mag_mul_2exp_fmpz(arb_radref(x), arb_radref(x), err);
        return;
    }

    mag_add_2exp_fmpz(arb_radref(x), arb_radref(x), err);
}

void
arb_add_error(arb_t x, const arb_t err)
{
    mag_t u;

    if (arb_is_zero(err))
        return;

    if (mag_is_zero(arb_radref(x)))
    {
        arb_get_mag(arb_radref(x), err);
        return;
    }

    mag_init(u);
    arb_get_mag(u, err);
    mag_add(arb_radref(x), arb_radref(x), u);
    mag_clear(u);
}

