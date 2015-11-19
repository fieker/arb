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

#include "arb_poly.h"

void
arb_poly_set_coeff_arb(arb_poly_t poly, slong n, const arb_t x)
{
    arb_poly_fit_length(poly, n + 1);

    if (n + 1 > poly->length)
    {
        _arb_vec_zero(poly->coeffs + poly->length, n - poly->length);
        poly->length = n + 1;
    }

    arb_set(poly->coeffs + n, x);
    _arb_poly_normalise(poly);
}

