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
    #define _SYS_STDIN_FILENO             _SYS_LINUX_STDIN_FILENO
    #define _SYS_STDOUT_FILENO            _SYS_LINUX_STDOUT_FILENO
    #define _SYS_STDERR_FILENO            _SYS_LINUX_STDERR_FILENO
    #define _SYS_O_RDONLY                 _SYS_LINUX_O_RDONLY
    #define _SYS_O_WRONLY                 _SYS_LINUX_O_WRONLY
    #define _SYS_O_RDWR                   _SYS_LINUX_O_RDWR
    #define _SYS_O_ACCMODE                _SYS_LINUX_O_ACCMODE
    #define _SYS_O_CREAT                  _SYS_LINUX_O_CREAT
    #define _SYS_O_EXCL                   _SYS_LINUX_O_EXCL
    #define _SYS_O_TRUNC                  _SYS_LINUX_O_TRUNC
    #define _SYS_O_APPEND                 _SYS_LINUX_O_APPEND
    #define _SYS_S_IRUSR                  _SYS_LINUX_S_IRUSR
    #define _SYS_S_IWUSR                  _SYS_LINUX_S_IWUSR
    #define _SYS_DEFFILEMODE              _SYS_LINUX_DEFFILEMODE
    #define _SYS_SEEK_SET                 _SYS_LINUX_SEEK_SET
    #define _SYS_SEEK_CUR                 _SYS_LINUX_SEEK_CUR
    #define _SYS_SEEK_END                 _SYS_LINUX_SEEK_END
    #define _SYS_CLOCK_REALTIME           _SYS_LINUX_CLOCK_REALTIME
    #define _SYS_CLOCK_PROCESS_CPUTIME_ID _SYS_LINUX_CLOCK_PROCESS_CPUTIME_ID
    #define _SYS_EIO                      _SYS_LINUX_EIO
    #define _SYS_EBADF                    _SYS_LINUX_EBADF
    #define _SYS_ENOMEM                   _SYS_LINUX_ENOMEM
    #define _SYS_EEXIST                   _SYS_LINUX_EEXIST
    #define _SYS_EINVAL                   _SYS_LINUX_EINVAL
    #define _SYS_EDOM                     _SYS_LINUX_EDOM
    #define _SYS_ERANGE                   _SYS_LINUX_ERANGE
    #define _SYS_ENOSYS                   _SYS_LINUX_ENOSYS
    #define _SYS_EOVERFLOW                _SYS_LINUX_EOVERFLOW
    #define _SYS_EILSEQ                   _SYS_LINUX_EILSEQ
    #define _Sys_Timespec                 _Sys_Linux_Timespec
    #define _Sys_ReadFile                 _Sys_Linux_ReadFile
    #define _Sys_WriteFile                _Sys_Linux_WriteFile
    #define _Sys_OpenFile                 _Sys_Linux_OpenFile
    #define _Sys_CloseFile                _Sys_Linux_CloseFile
    #define _Sys_SeekFile                 _Sys_Linux_SeekFile
    #define _Sys_CopyDescriptor           _Sys_Linux_CopyDescriptor
    #define _Sys_IsTerminal               _Sys_Linux_IsTerminal
    #define _Sys_RemoveFile               _Sys_Linux_RemoveFile
    #define _Sys_RenameFile               _Sys_Linux_RenameFile
    #define _Sys_IsNameUnused             _Sys_Linux_IsNameUnused
    #define _Sys_MoveBreak                _Sys_Linux_MoveBreak
    #define _Sys_SetSignal                _Sys_Linux_SetSignal
    #define _Sys_UnblockSignal            _Sys_Linux_UnblockSignal
    #define _Sys_RaiseSignal              _Sys_Linux_RaiseSignal
    #define _Sys_ReadClock                _Sys_Linux_ReadClock
    #define _Sys_ExitProgram              _Sys_Linux_ExitProgram
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
