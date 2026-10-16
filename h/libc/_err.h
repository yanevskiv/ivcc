/*
 * C header file for the texts a running program prints.
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

#ifndef _ERR_H
#define _ERR_H

#if defined(__linux__)
    #include <os/linux/_err.h>
#else
    #error "_err.h: no error texts for this OS"
#endif

// The string that is none.
#define _ERR_NULL ((char *) 0)

// The error number of no error.
#define _ERR_ERRNO_NONE 0

// The text strerror puts before an error number it does not know.
#define _ERR_STRING_UNKNOWN "Unknown error "

// The text assert's message puts after each of its parts.
#define _ERR_ASSERT_PROGRAM ": "
#define _ERR_ASSERT_FILE    ":"
#define _ERR_ASSERT_LINE    ": "
#define _ERR_ASSERT_FUNC    ": Assertion `"
#define _ERR_ASSERT_EXPR    "' failed.\n"

// The texts printf gives for a null string and a null pointer, as glibc's does.
#define _ERR_PRINT_NULL "(null)"
#define _ERR_PRINT_NIL  "(nil)"

// The texts printf gives for an infinity and a NaN, and those in capitals.
#define _ERR_PRINT_INF       "inf"
#define _ERR_PRINT_NAN       "nan"
#define _ERR_PRINT_INF_UPPER "INF"
#define _ERR_PRINT_NAN_UPPER "NAN"

// The text a failed check's report puts after each of its parts.
#define _ERR_TEST_FILE     ":"
#define _ERR_TEST_LINE     ": "
#define _ERR_TEST_FUNC     ": "
#define _ERR_TEST_FALSE    " is false\n"
#define _ERR_TEST_EXPR     " is "
#define _ERR_TEST_GOT      ", expected "
#define _ERR_TEST_EXPECTED "\n"

// The text a failed check's report gives for a string that is none.
#define _ERR_TEST_NULL "a null pointer"

// The text a failed check's report puts before a floating value's bytes.
#define _ERR_TEST_HEX "0x"

// strerror's texts by error number, null for the numbers Linux leaves out.
extern const char *const _Err_ErrnoTexts[_ERR_ERRNO_COUNT];

// The error number of the last failed call, which <errno.h> names errno.
extern int _Err_Errno;

// Error numbers
const char *_Err_FindErrnoText(int errnum);

#endif // _ERR_H
