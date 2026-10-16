/*
 * C header file for errors.
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

#ifndef _ERRNO_H
#define _ERRNO_H

#if defined(__linux__)
    #include <os/linux/errno.h>
#else
    #error "errno.h: no error numbers for this OS"
#endif

// Errors
// [C99:7.5]: EDOM, EILSEQ, ERANGE and errno
#define EDOM   _ERRNO_EDOM
#define EILSEQ _ERRNO_EILSEQ
#define ERANGE _ERRNO_ERANGE
#define errno  _Err_Errno

// The error number of the last failed call, which _err.c defines.
extern int _Err_Errno;

#endif // _ERRNO_H
