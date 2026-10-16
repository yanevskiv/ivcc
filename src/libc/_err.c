/*
 * C source file for the texts a running program prints.
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
#include <_err.h>

// The error number of the last failed call, which <errno.h> names errno.
int _Err_Errno;

// Find strerror's text for the error number errnum, null for an unknown.
const char *_Err_FindErrnoText(int errnum)
{
    if (errnum < 0 || errnum >= _ERR_ERRNO_COUNT) {
        return _ERR_NULL;
    }
    return _Err_ErrnoTexts[errnum];
}
