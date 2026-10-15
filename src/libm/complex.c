/*
 * C source file for complex arithmetic.
 *
 * Copyright (C) 2026 Ivan Janevski
 *
 * ivcc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * ivcc is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * Under Section 7 of GPL version 3, you are granted additional
 * permissions described in the GCC Runtime Library Exception, version
 * 3.1, as published by the Free Software Foundation.
 *
 * You should have received a copy of the GNU General Public License and
 * a copy of the GCC Runtime Library Exception along with ivcc; see
 * the files LICENSE and COPYING.RUNTIME respectively.  If not, see
 * <https://www.gnu.org/licenses/>.
 */


// Module header.
#include <complex.h>

// Includes.
#include <_basic_complex.h>

// Multiply a + ib by c + id, the compiler's helper for float.
float _Complex __mulsc3(float a, float b, float c, float d)
{
    return __basic_complex_mulsc3(a, b, c, d);
}

// Multiply a + ib by c + id, the compiler's helper for double.
double _Complex __muldc3(double a, double b, double c, double d)
{
    return __basic_complex_muldc3(a, b, c, d);
}

// Multiply a + ib by c + id, the compiler's helper for long double.
long double _Complex __mulxc3(long double a, long double b, long double c, long double d)
{
    return __basic_complex_mulxc3(a, b, c, d);
}

// Divide a + ib by c + id, the compiler's helper for float.
float _Complex __divsc3(float a, float b, float c, float d)
{
    return __basic_complex_divsc3(a, b, c, d);
}

// Divide a + ib by c + id, the compiler's helper for double.
double _Complex __divdc3(double a, double b, double c, double d)
{
    return __basic_complex_divdc3(a, b, c, d);
}

// Divide a + ib by c + id, the compiler's helper for long double.
long double _Complex __divxc3(long double a, long double b, long double c, long double d)
{
    return __basic_complex_divxc3(a, b, c, d);
}
