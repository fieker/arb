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
#include "hypgeom.h"

void
arb_const_log2_eval(arb_t s, slong prec)
{
    hypgeom_t series;
    arb_t t;

    arb_init(t);
    hypgeom_init(series);

    fmpz_poly_set_str(series->A, "1  1");
    fmpz_poly_set_str(series->B, "1  1");
    fmpz_poly_set_str(series->P, "2  0 -1");
    fmpz_poly_set_str(series->Q, "2  4 8");

    prec += FLINT_CLOG2(prec);
    arb_hypgeom_infsum(s, t, series, prec, prec);
    arb_mul_ui(s, s, 3, prec);
    arb_mul_2exp_si(t, t, 2);
    arb_div(s, s, t, prec);

    hypgeom_clear(series);
    arb_clear(t);
}

ARB_DEF_CACHED_CONSTANT(arb_const_log2, arb_const_log2_eval)

