/*
 * C source file for the system layer on Linux.
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
#include <_sys.h>

// errno, which an operation sets when it fails.
#include <_err.h>

// The set rt_sigprocmask gives back when the old one is not wanted.
#define _SYS_NO_SET ((unsigned long *) 0)

// The bytes of Linux's struct termios.
#define _SYS_TERMIOS_SIZE 36

// Check that struct termios is laid out as the kernel's.
_Static_assert(sizeof(_Sys_Termios) == _SYS_TERMIOS_SIZE, "_Sys_Termios should be the kernel's size");

// Read up to len bytes from the descriptor fd into buf, or -1 with errno.
long _Sys_ReadFile(int fd, void *buf, unsigned long len)
{
    return _Sys_CheckResult(_Sys_InvokeRead(fd, buf, len));
}

// Write len bytes of buf to the descriptor fd, or return -1 with errno.
long _Sys_WriteFile(int fd, const void *buf, unsigned long len)
{
    return _Sys_CheckResult(_Sys_InvokeWrite(fd, buf, len));
}

// Open the file at path as flags say, mode its permissions, or return -1.
int _Sys_OpenFile(const char *path, int flags, int mode)
{
    return (int) _Sys_CheckResult(_Sys_InvokeOpen(path, flags, mode));
}

// Close the descriptor fd, or return -1 with errno.
int _Sys_CloseFile(int fd)
{
    return (int) _Sys_CheckResult(_Sys_InvokeClose(fd));
}

// Move the descriptor fd's offset by offset from whence, and return it.
long _Sys_SeekFile(int fd, long offset, int whence)
{
    return _Sys_CheckResult(_Sys_InvokeLseek(fd, offset, whence));
}

// Copy the descriptor fd to as, closing what as was, or return -1.
int _Sys_CopyDescriptor(int fd, int as)
{
    return (int) _Sys_CheckResult(_Sys_InvokeDup2(fd, as));
}

// Return whether the descriptor fd is a terminal, errno left as it was.
_Bool _Sys_IsTerminal(int fd)
{
    _Sys_Termios term;

    return _Sys_InvokeIoctl(fd, _SYS_TCGETS, &term) == 0;
}

// Remove the file at path, or the empty directory there, or return -1.
int _Sys_RemoveFile(const char *path)
{
    long status = _Sys_InvokeUnlink(path);

    if (status == -_SYS_EISDIR) {
        status = _Sys_InvokeRmdir(path);
    }
    return (int) _Sys_CheckResult(status);
}

// Give the file at from the name to, replacing its holder, or return -1.
int _Sys_RenameFile(const char *from, const char *to)
{
    return (int) _Sys_CheckResult(_Sys_InvokeRename(from, to));
}

// Return whether no file has the name path, errno left as it was.
_Bool _Sys_IsNameUnused(const char *path)
{
    _Sys_Stat info;

    return _Sys_InvokeLstat(path, &info) == -_SYS_ENOENT;
}

// Move the program break to addr, and return where it stands.
void *_Sys_MoveBreak(void *addr)
{
    return _Sys_InvokeBrk(addr);
}

// Install func as the handler of sig, the old one in old, or return -1.
int _Sys_SetSignal(int sig, void (*func)(int), void (**old)(int))
{
    if (sig < _SYS_SIGNAL_FIRST || sig > _SYS_SIGNAL_LAST) {
        _Err_Errno = _SYS_EINVAL;
        return -1;
    }
    return (int) _Sys_CheckResult(_Sys_InvokeRtSigaction(sig, func, _SYS_SA_RESTART, 1UL << (sig - _SYS_SIGNAL_FIRST), old));
}

// Unblock the signal sig, or return -1 with errno.
int _Sys_UnblockSignal(int sig)
{
    unsigned long set = 1UL << (sig - _SYS_SIGNAL_FIRST);

    return (int) _Sys_CheckResult(_Sys_InvokeRtSigprocmask(_SYS_SIG_UNBLOCK, &set, _SYS_NO_SET));
}

// Send the signal sig to the program, or return -1 with errno.
int _Sys_RaiseSignal(int sig)
{
    return (int) _Sys_CheckResult(_Sys_InvokeKill(_Sys_InvokeGetpid(), sig));
}

// Read the clock clock into spec, or return -1 with errno.
int _Sys_ReadClock(int clock, _Sys_Timespec *spec)
{
    return (int) _Sys_CheckResult(_Sys_InvokeClockGettime(clock, spec));
}

// End the program, every thread of it, with status.
void _Sys_ExitProgram(int status)
{
    _Sys_InvokeExitGroup(status);
}

// Return ret, a syscall's result, or -1 with errno for one that is -errno.
long _Sys_CheckResult(long ret)
{
    if (ret < 0) {
        _Err_Errno = (int) -ret;
        return -1;
    }
    return ret;
}
