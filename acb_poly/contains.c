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

#include "acb_poly.h"

int
acb_poly_contains(const acb_poly_t poly1, const acb_poly_t poly2)
{
    slong i;

    if (poly2->length > poly1->length)
        return 0;

    for (i = 0; i < poly2->length; i++)
    {
        if (!acb_contains(poly1->coeffs + i, poly2->coeffs + i))
            return 0;
    }

    for (i = poly2->length; i < poly1->length; i++)
        if (!acb_contains_zero(poly1->coeffs + i))
            return 0;

    return 1;
}
