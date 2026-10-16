/*
 * C header file for the system layer.
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

#ifndef _SYS_H
#define _SYS_H

#if defined(__linux__)
    #include <os/linux/_sys.h>
#else
    #error "_sys.h: no system layer for this OS"
#endif

// Files
long  _Sys_ReadFile(int fd, void *buf, unsigned long len);
long  _Sys_WriteFile(int fd, const void *buf, unsigned long len);
int   _Sys_OpenFile(const char *path, int flags, int mode);
int   _Sys_CloseFile(int fd);
long  _Sys_SeekFile(int fd, long offset, int whence);
int   _Sys_CopyDescriptor(int fd, int as);
_Bool _Sys_IsTerminal(int fd);

// Names
int   _Sys_RemoveFile(const char *path);
int   _Sys_RenameFile(const char *from, const char *to);
_Bool _Sys_IsNameUnused(const char *path);

// Memory
void *_Sys_MoveBreak(void *addr);

// Signals
int _Sys_SetSignal(int sig, void (*func)(int), void (**old)(int));
int _Sys_UnblockSignal(int sig);
int _Sys_RaiseSignal(int sig);

// Time
int _Sys_ReadClock(int clock, _Sys_Timespec *spec);

// Exit
void _Sys_ExitProgram(int status);

#endif // _SYS_H
