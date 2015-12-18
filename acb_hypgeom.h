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

#ifndef ACB_HYPGEOM_H
#define ACB_HYPGEOM_H

#include "acb.h"
#include "acb_poly.h"

#ifdef __cplusplus
extern "C" {
#endif

void acb_hypgeom_pfq_bound_factor(mag_t C,
    acb_srcptr a, slong p, acb_srcptr b, slong q, const acb_t z, ulong n);

slong acb_hypgeom_pfq_choose_n(acb_srcptr a, slong p,
                         acb_srcptr b, slong q, const acb_t z, slong prec);

void acb_hypgeom_pfq_sum_forward(acb_t s, acb_t t, acb_srcptr a, slong p, acb_srcptr b, slong q,
    const acb_t z, slong n, slong prec);

void acb_hypgeom_pfq_sum_rs(acb_t s, acb_t t, acb_srcptr a, slong p, acb_srcptr b, slong q,
    const acb_t z, slong n, slong prec);

void acb_hypgeom_pfq_sum_bs(acb_t s, acb_t t, acb_srcptr a, slong p, acb_srcptr b, slong q,
    const acb_t z, slong n, slong prec);

void acb_hypgeom_pfq_sum_fme(acb_t s, acb_t t, acb_srcptr a, slong p, acb_srcptr b, slong q,
    const acb_t z, slong n, slong prec);

void acb_hypgeom_pfq_sum(acb_t s, acb_t t, acb_srcptr a, slong p, acb_srcptr b, slong q,
    const acb_t z, slong n, slong prec);

void acb_hypgeom_pfq_sum_bs_invz(acb_t s, acb_t t,
    acb_srcptr a, slong p, acb_srcptr b, slong q, const acb_t z, slong n, slong prec);

void acb_hypgeom_pfq_sum_invz(acb_t s, acb_t t, acb_srcptr a, slong p,
    acb_srcptr b, slong q, const acb_t z, const acb_t zinv, slong n, slong prec);

void acb_hypgeom_pfq_direct(acb_t res, acb_srcptr a, slong p, acb_srcptr b, slong q,
    const acb_t z, slong n, slong prec);

slong acb_hypgeom_pfq_series_choose_n(const acb_poly_struct * a, slong p,
                                const acb_poly_struct * b, slong q,
                                const acb_poly_t z, slong len, slong prec);

void acb_hypgeom_pfq_series_direct(acb_poly_t res,
    const acb_poly_struct * a, slong p,
    const acb_poly_struct * b, slong q,
    const acb_poly_t z, int regularized,
    slong n, slong len, slong prec);

void acb_hypgeom_u_asymp(acb_t res, const acb_t a, const acb_t b,
    const acb_t z, slong n, slong prec);

void acb_hypgeom_u_1f1_series(acb_poly_t res,
    const acb_poly_t a, const acb_poly_t b, const acb_poly_t z,
    slong len, slong prec);

void acb_hypgeom_u_1f1(acb_t res, const acb_t a, const acb_t b, const acb_t z, slong prec);
void acb_hypgeom_u(acb_t res, const acb_t a, const acb_t b, const acb_t z, slong prec);

int acb_hypgeom_u_use_asymp(const acb_t z, slong prec);

void acb_hypgeom_m_asymp(acb_t res, const acb_t a, const acb_t b, const acb_t z, int regularized, slong prec);
void acb_hypgeom_m_1f1(acb_t res, const acb_t a, const acb_t b, const acb_t z, int regularized, slong prec);
void acb_hypgeom_m(acb_t res, const acb_t a, const acb_t b, const acb_t z, int regularized, slong prec);

void acb_hypgeom_erf_1f1a(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_erf_1f1b(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_erf_asymp(acb_t res, const acb_t z, slong prec, slong prec2);
void acb_hypgeom_erf(acb_t res, const acb_t z, slong prec);

void acb_hypgeom_bessel_j_0f1(acb_t res, const acb_t nu, const acb_t z, slong prec);
void acb_hypgeom_bessel_j_asymp(acb_t res, const acb_t nu, const acb_t z, slong prec);
void acb_hypgeom_bessel_j(acb_t res, const acb_t nu, const acb_t z, slong prec);

void acb_hypgeom_bessel_i_0f1(acb_t res, const acb_t nu, const acb_t z, slong prec);
void acb_hypgeom_bessel_i_asymp(acb_t res, const acb_t nu, const acb_t z, slong prec);
void acb_hypgeom_bessel_i(acb_t res, const acb_t nu, const acb_t z, slong prec);

void acb_hypgeom_bessel_k_0f1(acb_t res, const acb_t nu, const acb_t z, slong prec);
void acb_hypgeom_bessel_k_0f1_series(acb_poly_t res, const acb_poly_t n, const acb_poly_t z, slong len, slong prec);
void acb_hypgeom_bessel_k_asymp(acb_t res, const acb_t nu, const acb_t z, slong prec);
void acb_hypgeom_bessel_k(acb_t res, const acb_t nu, const acb_t z, slong prec);

void acb_hypgeom_bessel_y(acb_t res, const acb_t nu, const acb_t z, slong prec);
void acb_hypgeom_bessel_jy(acb_t res1, acb_t res2, const acb_t nu, const acb_t z, slong prec);

void acb_hypgeom_0f1_asymp(acb_t res, const acb_t a, const acb_t z, int regularized, slong prec);
void acb_hypgeom_0f1_direct(acb_t res, const acb_t a, const acb_t z, int regularized, slong prec);
void acb_hypgeom_0f1(acb_t res, const acb_t a, const acb_t z, int regularized, slong prec);

void acb_hypgeom_airy_bound(mag_t ai, mag_t aip, mag_t bi, mag_t bip, const acb_t z);
void acb_hypgeom_airy_asymp(acb_t ai, acb_t aip, acb_t bi, acb_t bip, const acb_t z, slong n, slong prec);
void acb_hypgeom_airy_direct(acb_t ai, acb_t aip, acb_t bi, acb_t bip, const acb_t z, slong n, slong prec);
void acb_hypgeom_airy(acb_t ai, acb_t aip, acb_t bi, acb_t bip, const acb_t z, slong prec);

void acb_hypgeom_gamma_upper_asymp(acb_t res, const acb_t s, const acb_t z, int modified, slong prec);
void acb_hypgeom_gamma_upper_1f1a(acb_t res, const acb_t s, const acb_t z, int modified, slong prec);
void acb_hypgeom_gamma_upper_1f1b(acb_t res, const acb_t s, const acb_t z, int modified, slong prec);
void acb_hypgeom_gamma_upper_singular(acb_t res, slong s, const acb_t z, int modified, slong prec);
void acb_hypgeom_gamma_upper(acb_t res, const acb_t s, const acb_t z, int modified, slong prec);

void acb_hypgeom_expint(acb_t res, const acb_t s, const acb_t z, slong prec);

void acb_hypgeom_erfc(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_erfi(acb_t res, const acb_t z, slong prec);

void acb_hypgeom_ei_asymp(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_ei_2f2(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_ei(acb_t res, const acb_t z, slong prec);

void acb_hypgeom_si_asymp(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_si_1f2(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_si(acb_t res, const acb_t z, slong prec);

void acb_hypgeom_ci_asymp(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_ci_2f3(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_ci(acb_t res, const acb_t z, slong prec);

void acb_hypgeom_shi(acb_t res, const acb_t z, slong prec);

void acb_hypgeom_chi_asymp(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_chi_2f3(acb_t res, const acb_t z, slong prec);
void acb_hypgeom_chi(acb_t res, const acb_t z, slong prec);

void acb_hypgeom_li(acb_t res, const acb_t z, int offset, slong prec);

void acb_hypgeom_2f1_continuation(acb_t res0, acb_t res1,
    const acb_t a, const acb_t b, const acb_t c, const acb_t z0,
    const acb_t z1, const acb_t f0, const acb_t f1, slong prec);

void acb_hypgeom_2f1_series_direct(acb_poly_t res, const acb_poly_t a, const acb_poly_t b,
    const acb_poly_t c, const acb_poly_t z, int regularized, slong len, slong prec);
void acb_hypgeom_2f1_direct(acb_t res, const acb_t a, const acb_t b, const acb_t c, const acb_t z, int regularized, slong prec);

void acb_hypgeom_2f1_transform(acb_t res, const acb_t a, const acb_t b,
    const acb_t c, const acb_t z, int regularized, int which, slong prec);

void acb_hypgeom_2f1_transform_limit(acb_t res, const acb_t a, const acb_t b,
    const acb_t c, const acb_t z, int regularized, int which, slong prec);

void acb_hypgeom_2f1_corner(acb_t res, const acb_t a, const acb_t b, const acb_t c, const acb_t z, int regularized, slong prec);

int acb_hypgeom_2f1_choose(const acb_t z);

void acb_hypgeom_2f1(acb_t res, const acb_t a, const acb_t b, const acb_t c, const acb_t z, int regularized, slong prec);

void acb_hypgeom_legendre_p_uiui_rec(acb_t res, ulong n, ulong m, const acb_t z, slong prec);
void acb_hypgeom_legendre_p(acb_t res, const acb_t n, const acb_t m, const acb_t z, int type, slong prec);
void acb_hypgeom_legendre_q(acb_t res, const acb_t n, const acb_t m, const acb_t z, int type, slong prec);
void acb_hypgeom_jacobi_p(acb_t res, const acb_t n, const acb_t a, const acb_t b, const acb_t z, slong prec);
void acb_hypgeom_gegenbauer_c(acb_t res, const acb_t n, const acb_t m, const acb_t z, slong prec);
void acb_hypgeom_laguerre_l(acb_t res, const acb_t n, const acb_t m, const acb_t z, slong prec);
void acb_hypgeom_hermite_h(acb_t res, const acb_t n, const acb_t z, slong prec);
void acb_hypgeom_chebyshev_t(acb_t res, const acb_t n, const acb_t z, slong prec);
void acb_hypgeom_chebyshev_u(acb_t res, const acb_t n, const acb_t z, slong prec);
void acb_hypgeom_spherical_y(acb_t res, slong n, slong m, const acb_t theta, const acb_t phi, slong prec);

#ifdef __cplusplus
}
#endif

#endif

