/*
 * C header file for signal handling on Linux.
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

#ifndef _OS_LINUX_SIGNAL_H
#define _OS_LINUX_SIGNAL_H

// Linux's numbers for C99's six signals.
#define _SIGNAL_SIGABRT 6
#define _SIGNAL_SIGFPE  8
#define _SIGNAL_SIGILL  4
#define _SIGNAL_SIGINT  2
#define _SIGNAL_SIGSEGV 11
#define _SIGNAL_SIGTERM 15

#endif // _OS_LINUX_SIGNAL_H
