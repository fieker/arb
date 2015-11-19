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

    Copyright (C) 2012 Fredrik Johansson

******************************************************************************/

#include "fmprb.h"

void
fmprb_submul(fmprb_t z, const fmprb_t x, const fmprb_t y, slong prec)
{
    fmprb_t t;

    fmprb_init(t);
    fmprb_mul(t, x, y, prec);
    fmprb_sub(z, z, t, prec);
    fmprb_clear(t);
}

void
fmprb_submul_ui(fmprb_t z, const fmprb_t x, ulong y, slong prec)
{
    fmprb_t t;

    fmprb_init(t);
    fmprb_mul_ui(t, x, y, prec);
    fmprb_sub(z, z, t, prec);
    fmprb_clear(t);
}

void
fmprb_submul_si(fmprb_t z, const fmprb_t x, slong y, slong prec)
{
    fmprb_t t;

    fmprb_init(t);
    fmprb_sub_si(t, x, y, prec);
    fmprb_sub(z, z, t, prec);
    fmprb_clear(t);
}

void
fmprb_submul_fmpz(fmprb_t z, const fmprb_t x, const fmpz_t y, slong prec)
{
    fmprb_t t;

    fmprb_init(t);
    fmprb_mul_fmpz(t, x, y, prec);
    fmprb_sub(z, z, t, prec);
    fmprb_clear(t);
}
