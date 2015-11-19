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

#include "acb_poly.h"

void
_acb_poly_evaluate_rectangular(acb_t y, acb_srcptr poly,
    slong len, const acb_t x, slong prec)
{
    slong i, j, m, r;
    acb_ptr xs;
    acb_t s, t, c;

    if (len < 3)
    {
        if (len == 0)
        {
            acb_zero(y);
        }
        else if (len == 1)
        {
            acb_set_round(y, poly + 0, prec);
        }
        else if (len == 2)
        {
            acb_mul(y, x, poly + 1, prec);
            acb_add(y, y, poly + 0, prec);
        }
        return;
    }

    m = n_sqrt(len) + 1;
    r = (len + m - 1) / m;

    xs = _acb_vec_init(m + 1);
    acb_init(s);
    acb_init(t);
    acb_init(c);

    _acb_vec_set_powers(xs, x, m + 1, prec);

    acb_set(y, poly + (r - 1) * m);
    for (j = 1; (r - 1) * m + j < len; j++)
        acb_addmul(y, xs + j, poly + (r - 1) * m + j, prec);

    for (i = r - 2; i >= 0; i--)
    {
        acb_set(s, poly + i * m);
        for (j = 1; j < m; j++)
            acb_addmul(s, xs + j, poly + i * m + j, prec);

        acb_mul(y, y, xs + m, prec);
        acb_add(y, y, s, prec);
    }

    _acb_vec_clear(xs, m + 1);
    acb_clear(s);
    acb_clear(t);
    acb_clear(c);
}

void
acb_poly_evaluate_rectangular(acb_t res, const acb_poly_t f, const acb_t a, slong prec)
{
    _acb_poly_evaluate_rectangular(res, f->coeffs, f->length, a, prec);
}

