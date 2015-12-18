# Arb

Arb is a C library for arbitrary-precision interval arithmetic.
It has full support for both real and complex numbers.
The library is thread-safe, portable, and extensively tested.

![arb logo](http://fredrikj.net/blog/2015/01/arb-2-5-0-released/arbtext.png)

Documentation: http://fredrikj.net/arb/

Development updates: http://fredrikj.net/blog/

Author: Fredrik Johansson <fredrik.johansson@gmail.com>

Bug reports, feature requests and other comments are welcome
in private communication, on the GitHub issue tracker, or on the FLINT mailing list <flint-devel@googlegroups.com>.

## Code example

The following program evaluates `sin(pi + exp(-10000))`. Since the
input to the sine function matches a root to within 4343 digits,
at least 4343-digit (14427-bit) precision is needed to get an accurate
result. The program repeats the evaluation
at 64-bit, 128-bit, ... precision, stopping only when the
result is accurate to at least 53 bits.

    #include "arb.h"

    int main()
    {
        slong prec;
        arb_t x, y;
        arb_init(x); arb_init(y);

        for (prec = 64; ; prec *= 2)
        {
            arb_const_pi(x, prec);
            arb_set_si(y, -10000);
            arb_exp(y, y, prec);
            arb_add(x, x, y, prec);
            arb_sin(y, x, prec);
            arb_printn(y, 15, 0); printf("\n");
            if (arb_rel_accuracy_bits(y) >= 53)
                break;
        }

        arb_clear(x); arb_clear(y);
        flint_cleanup();
    }

The output is:

    [+/- 6.01e-19]
    [+/- 2.55e-38]
    [+/- 8.01e-77]
    [+/- 8.64e-154]
    [+/- 5.37e-308]
    [+/- 3.63e-616]
    [+/- 1.07e-1232]
    [+/- 9.27e-2466]
    [-1.13548386531474e-4343 +/- 3.91e-4358]

Each line shows a rigorous enclosure of the exact value
of the expression. The program demonstrates how the user
can rely on Arb's automatic error bound tracking to get an output
that is guaranteed to be accurate -- no error analysis
needs to be done by the user.

For several other example programs, see: http://fredrikj.net/arb/examples.html

## General features

Besides basic arithmetic, Arb allows working with univariate
polynomials, truncated power series, and matrices
over both real and complex numbers.

Basic linear algebra is supported, including matrix multiplication,
determinant, inverse, nonsingular solving and matrix exponential.

Support for polynomial and power series is quite extensive,
including methods for composition, reversion, product trees,
multipoint evaluation and interpolation, complex root isolation,
and transcendental functions of power series.

Arb has partial support for automatic differentiation (AD), and includes
rudimentary functionality for rigorous calculus based on AD
(including real root isolation and complex integration).

## Special functions

Arb can compute a wide range of transcendental and special functions,
including the gamma function, polygamma functions,
Riemann zeta and Hurwitz zeta function, polylogarithm,
error function, Gauss hypergeometric function 2F1, confluent
hypergeometric functions, Bessel functions, Airy functions,
Legendre functions and other orthogonal polynomials,
exponential and trigonometric integrals, incomplete gamma function,
Jacobi theta functions, modular functions, Weierstrass elliptic function,
complete elliptic integrals, arithmetic-geometric mean,
Bernoulli numbers, partition function, Barnes G-function.

## Speed

Arb uses a midpoint-radius (ball) representation of real numbers.
At high precision, this allows doing interval arithmetic without
significant overhead compared to plain floating-point arithmetic.
Various low-level optimizations have also been implemented
to reduce overhead at precisions of just a few machine
words. Most operations on polynomials and power series
use asymptotically fast FFT multiplication.

For basic arithmetic, Arb should generally be around as fast
as MPFR (http://mpfr.org), though it can be a bit slower
at low precision, and around twice as fast as MPFI
(https://perso.ens-lyon.fr/nathalie.revol/software.html).

Transcendental functions in Arb are quite well optimized and
should generally be faster than any other arbitrary-precision
software currently available. The following table
compares the time in seconds to evaluate the Gauss
hypergeometric function `2F1(1/2, 1/4, 1, z)` at
the complex number `z = 5^(1/2) + 7^(1/2)i`, to a given
number of decimal digits (Arb 2.8-git and mpmath 0.19 on
an 1.90 GHz Intel i5-4300U, Mathematica 9.0 on a 3.07 GHz Intel Xeon X5675).

| Digits  | Mathematica |     mpmath |      Arb  |
| -------:|:------------|:-----------|:----------|
|      10 |     0.00066 |    0.00090 |   0.00011 |
|     100 |     0.0039  |    0.0017  |   0.00075 |
|    1000 |     0.23    |    1.5     |   0.019   |
|   10000 |     42.6    |    98      |   1.2     |

## Dependencies, installation, and interfaces

Arb depends on FLINT (http://flintlib.org/), either
GMP (http://gmplib.org) or MPIR (http://mpir.org),
and MPFR (http://mpfr.org). 

See http://fredrikj.net/arb/setup.html for instructions
on building and installing Arb directly from the source code.
Arb might also be available (or coming soon) as a package for
your Linux distribution.

SageMath <http://sagemath.org/> will include Arb as a standard package
in an upcoming version, including a high-level Python interface
to Arb as part of the SageMath standard library.

Nemo <http://nemocas.org/> is a computer algebra package for
the Julia programming language which includes a high-level
Julia interface to Arb. The Nemo installation script will
create a local installation of Arb along with other dependencies.
