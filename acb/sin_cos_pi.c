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

#include "acb.h"

void
acb_sin_cos_pi(acb_t s, acb_t c, const acb_t z, slong prec)
{
#define a acb_realref(z)
#define b acb_imagref(z)

    arb_t sa, ca, sb, cb;

    arb_init(sa);
    arb_init(ca);
    arb_init(sb);
    arb_init(cb);

    arb_const_pi(sb, prec);
    arb_mul(sb, sb, b, prec);

    arb_sin_cos_pi(sa, ca, a, prec);
    arb_sinh_cosh(sb, cb, sb, prec);

    arb_mul(acb_realref(s), sa, cb, prec);
    arb_mul(acb_imagref(s), sb, ca, prec);

    arb_mul(acb_realref(c), ca, cb, prec);
    arb_mul(acb_imagref(c), sa, sb, prec);
    arb_neg(acb_imagref(c), acb_imagref(c));

    arb_clear(sa);
    arb_clear(ca);
    arb_clear(sb);
    arb_clear(cb);
}

