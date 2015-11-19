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

#include "acb_mat.h"

void
acb_mat_printd(const acb_mat_t mat, slong digits)
{
    slong i, j;

    for (i = 0; i < acb_mat_nrows(mat); i++)
    {
        flint_printf("[");

        for (j = 0; j < acb_mat_ncols(mat); j++)
        {
            acb_printd(acb_mat_entry(mat, i, j), digits);

            if (j < acb_mat_ncols(mat) - 1)
                flint_printf(", ");
        }

        flint_printf("]\n");
    }
}
