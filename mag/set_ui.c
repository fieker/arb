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

#include "mag.h"

void
mag_set_ui(mag_t z, ulong x)
{
    _fmpz_demote(MAG_EXPREF(z));

    if (x == 0)
    {
        MAG_EXP(z) = 0;
        MAG_MAN(z) = 0;
    }
    else
    {
        long bits;
        mp_limb_t overflow;

        count_leading_zeros(bits, x);
        bits = FLINT_BITS - bits;

        if (bits <= MAG_BITS)
        {
            x = x << (MAG_BITS - bits);
        }
        else
        {
            x = (x >> (bits - MAG_BITS)) + 1;
            overflow = x >> MAG_BITS;
            bits += overflow;
            x >>= overflow;
        }

        MAG_EXP(z) = bits;
        MAG_MAN(z) = x;
    }
}

void
mag_set_ui_lower(mag_t z, ulong x)
{
    _fmpz_demote(MAG_EXPREF(z));

    if (x == 0)
    {
        MAG_EXP(z) = 0;
        MAG_MAN(z) = 0;
    }
    else
    {
        unsigned int bits;

        count_leading_zeros(bits, x);
        bits = FLINT_BITS - bits;

        if (bits <= MAG_BITS)
            x <<= (MAG_BITS - bits);
        else
            x >>= (bits - MAG_BITS);

        MAG_EXP(z) = bits;
        MAG_MAN(z) = x;
    }
}

