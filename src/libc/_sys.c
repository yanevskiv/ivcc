/*
 * C source file for the system layer.
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

#ifndef __linux__
    #error "_sys.c: the system layer is Linux's alone"
#endif

// Linux's syscall numbers on x86-64.
#define _SYS_X86_64_LINUX_NR_READ           0
#define _SYS_X86_64_LINUX_NR_WRITE          1
#define _SYS_X86_64_LINUX_NR_OPEN           2
#define _SYS_X86_64_LINUX_NR_CLOSE          3
#define _SYS_X86_64_LINUX_NR_LSTAT          6
#define _SYS_X86_64_LINUX_NR_LSEEK          8
#define _SYS_X86_64_LINUX_NR_BRK            12
#define _SYS_X86_64_LINUX_NR_RT_SIGACTION   13
#define _SYS_X86_64_LINUX_NR_RT_SIGPROCMASK 14
#define _SYS_X86_64_LINUX_NR_IOCTL          16
#define _SYS_X86_64_LINUX_NR_DUP2           33
#define _SYS_X86_64_LINUX_NR_GETPID         39
#define _SYS_X86_64_LINUX_NR_KILL           62
#define _SYS_X86_64_LINUX_NR_RENAME         82
#define _SYS_X86_64_LINUX_NR_RMDIR          84
#define _SYS_X86_64_LINUX_NR_UNLINK         87
#define _SYS_X86_64_LINUX_NR_CLOCK_GETTIME  228
#define _SYS_X86_64_LINUX_NR_EXIT_GROUP     231

// The bytes of Linux's struct stat on x86-64.
#define _SYS_X86_64_LINUX_STAT_SIZE 144

// The bytes of Linux's sigset_t on x86-64.
#define _SYS_X86_64_LINUX_SIGSET_SIZE 8

// Linux's rt_sigreturn number on x86-64, as the restorer's assembly writes it.
#define _SYS_X86_64_LINUX_NR_RT_SIGRETURN "15"

// The set rt_sigprocmask gives back when the old one is not wanted.
#define _SYS_LINUX_NO_SET ((unsigned long *) 0)

// The bytes of Linux's struct termios.
#define _SYS_LINUX_TERMIOS_SIZE 36

// Check that struct stat is as large as the kernel's on x86-64.
_Static_assert(sizeof(_Sys_x86_64_Linux_Stat) == _SYS_X86_64_LINUX_STAT_SIZE, "_Sys_x86_64_Linux_Stat should be the kernel's size");

// Check that struct termios is laid out as the kernel's.
_Static_assert(sizeof(_Sys_Linux_Termios) == _SYS_LINUX_TERMIOS_SIZE, "_Sys_Linux_Termios should be the kernel's size");

#ifdef __x86_64__
// Invoke a syscall by its number, with six arguments.
__asm__(
    "  .text\n"
    "  .globl _Sys_x86_64_Linux_InvokeSyscall\n"
    "_Sys_x86_64_Linux_InvokeSyscall:\n"
    "  mov %rdi, %rax\n"
    "  mov %rsi, %rdi\n"
    "  mov %rdx, %rsi\n"
    "  mov %rcx, %rdx\n"
    "  mov %r8, %r10\n"
    "  mov %r9, %r8\n"
    "  mov 8(%rsp), %r9\n"
    "  syscall\n"
    "  ret\n"
);
#else
    #error "_sys.c: no system calls for this architecture"
#endif

// Invoke read to read up to len bytes from the descriptor fd into buf.
long _Sys_x86_64_Linux_InvokeRead(int fd, void *buf, unsigned long len)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_READ, fd, (long) buf, (long) len, 0, 0, 0);
}

// Invoke write to write len bytes of buf to the descriptor fd.
long _Sys_x86_64_Linux_InvokeWrite(int fd, const void *buf, unsigned long len)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_WRITE, fd, (long) buf, (long) len, 0, 0, 0);
}

// Invoke open to open the file at path as flags say, mode its permissions.
long _Sys_x86_64_Linux_InvokeOpen(const char *path, int flags, int mode)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_OPEN, (long) path, flags, mode, 0, 0, 0);
}

// Invoke close to close the descriptor fd.
long _Sys_x86_64_Linux_InvokeClose(int fd)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_CLOSE, fd, 0, 0, 0, 0, 0);
}

// Invoke lstat to fill info with what the file at path is, a link's own.
long _Sys_x86_64_Linux_InvokeLstat(const char *path, _Sys_x86_64_Linux_Stat *info)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_LSTAT, (long) path, (long) info, 0, 0, 0, 0);
}

// Invoke lseek to move the descriptor fd's offset by offset from whence.
long _Sys_x86_64_Linux_InvokeLseek(int fd, long offset, int whence)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_LSEEK, fd, offset, whence, 0, 0, 0);
}

// Invoke brk to move the program break to addr, and return where it stands.
void *_Sys_x86_64_Linux_InvokeBrk(void *addr)
{
    return (void *) _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_BRK, (long) addr, 0, 0, 0, 0, 0);
}

// Invoke rt_sigaction to install func for sig, the old handler in old.
long _Sys_x86_64_Linux_InvokeRtSigaction(int sig, void (*func)(int), unsigned long flags, unsigned long mask, void (**old)(int))
{
    _Sys_x86_64_Linux_Sigaction act;
    _Sys_x86_64_Linux_Sigaction prev;
    long ret;

    act.sa_handler = func;
    act.sa_flags = flags | _SYS_X86_64_LINUX_SA_RESTORER;
    act.sa_restorer = _Sys_x86_64_Linux_InvokeRtSigreturn;
    act.sa_mask = mask;
    ret = _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_RT_SIGACTION, sig, (long) &act, (long) &prev, _SYS_X86_64_LINUX_SIGSET_SIZE, 0, 0);
    if (ret == 0) {
        *old = prev.sa_handler;
    }
    return ret;
}

// Invoke rt_sigprocmask to change the mask by how and set, the old in oset.
long _Sys_x86_64_Linux_InvokeRtSigprocmask(int how, const unsigned long *set, unsigned long *oset)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_RT_SIGPROCMASK, how, (long) set, (long) oset, _SYS_X86_64_LINUX_SIGSET_SIZE, 0, 0);
}

// Invoke ioctl to make the request request of the descriptor fd, with arg.
long _Sys_x86_64_Linux_InvokeIoctl(int fd, unsigned long request, void *arg)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_IOCTL, fd, (long) request, (long) arg, 0, 0, 0);
}

// Invoke dup2 to make the descriptor as a copy of fd, closing what it was.
long _Sys_x86_64_Linux_InvokeDup2(int fd, int as)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_DUP2, fd, as, 0, 0, 0, 0);
}

// Invoke getpid to return the program's process ID.
int _Sys_x86_64_Linux_InvokeGetpid(void)
{
    return (int) _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_GETPID, 0, 0, 0, 0, 0, 0);
}

// Invoke kill to send the signal sig to the process pid.
long _Sys_x86_64_Linux_InvokeKill(int pid, int sig)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_KILL, pid, sig, 0, 0, 0, 0);
}

// Invoke rename to give the file at from the name to, replacing its holder.
long _Sys_x86_64_Linux_InvokeRename(const char *from, const char *to)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_RENAME, (long) from, (long) to, 0, 0, 0, 0);
}

// Invoke rmdir to remove the empty directory at path.
long _Sys_x86_64_Linux_InvokeRmdir(const char *path)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_RMDIR, (long) path, 0, 0, 0, 0, 0);
}

// Invoke unlink to remove the name path from its file.
long _Sys_x86_64_Linux_InvokeUnlink(const char *path)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_UNLINK, (long) path, 0, 0, 0, 0, 0);
}

// Invoke clock_gettime to read the clock clock into spec.
long _Sys_x86_64_Linux_InvokeClockGettime(int clock, _Sys_Linux_Timespec *spec)
{
    return _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_CLOCK_GETTIME, clock, (long) spec, 0, 0, 0, 0);
}

// Invoke exit_group to end the program, every thread of it, with a status.
void _Sys_x86_64_Linux_InvokeExitGroup(int status)
{
    _Sys_x86_64_Linux_InvokeSyscall(_SYS_X86_64_LINUX_NR_EXIT_GROUP, status, 0, 0, 0, 0, 0);
}

#ifdef __x86_64__
// Invoke rt_sigreturn to return from a handler to what the signal interrupted.
__asm__(
    "  .text\n"
    "  .globl _Sys_x86_64_Linux_InvokeRtSigreturn\n"
    "_Sys_x86_64_Linux_InvokeRtSigreturn:\n"
    "  mov $" _SYS_X86_64_LINUX_NR_RT_SIGRETURN ", %rax\n"
    "  syscall\n"
);
#else
    #error "_sys.c: no signal handlers for this architecture"
#endif

// Read up to len bytes from the descriptor fd into buf, or -1 with errno.
long _Sys_Linux_ReadFile(int fd, void *buf, unsigned long len)
{
    return _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeRead(fd, buf, len));
}

// Write len bytes of buf to the descriptor fd, or return -1 with errno.
long _Sys_Linux_WriteFile(int fd, const void *buf, unsigned long len)
{
    return _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeWrite(fd, buf, len));
}

// Open the file at path as flags say, mode its permissions, or return -1.
int _Sys_Linux_OpenFile(const char *path, int flags, int mode)
{
    return (int) _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeOpen(path, flags, mode));
}

// Close the descriptor fd, or return -1 with errno.
int _Sys_Linux_CloseFile(int fd)
{
    return (int) _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeClose(fd));
}

// Move the descriptor fd's offset by offset from whence, and return it.
long _Sys_Linux_SeekFile(int fd, long offset, int whence)
{
    return _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeLseek(fd, offset, whence));
}

// Copy the descriptor fd to as, closing what as was, or return -1.
int _Sys_Linux_CopyDescriptor(int fd, int as)
{
    return (int) _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeDup2(fd, as));
}

// Return whether the descriptor fd is a terminal, errno left as it was.
_Bool _Sys_Linux_IsTerminal(int fd)
{
    _Sys_Linux_Termios term;

    return _Sys_x86_64_Linux_InvokeIoctl(fd, _SYS_LINUX_TCGETS, &term) == 0;
}

// Remove the file at path, or the empty directory there, or return -1.
int _Sys_Linux_RemoveFile(const char *path)
{
    long status = _Sys_x86_64_Linux_InvokeUnlink(path);

    if (status == -_SYS_LINUX_EISDIR) {
        status = _Sys_x86_64_Linux_InvokeRmdir(path);
    }
    return (int) _Sys_Linux_CheckResult(status);
}

// Give the file at from the name to, replacing its holder, or return -1.
int _Sys_Linux_RenameFile(const char *from, const char *to)
{
    return (int) _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeRename(from, to));
}

// Return whether no file has the name path, errno left as it was.
_Bool _Sys_Linux_IsNameUnused(const char *path)
{
    _Sys_x86_64_Linux_Stat info;

    return _Sys_x86_64_Linux_InvokeLstat(path, &info) == -_SYS_LINUX_ENOENT;
}

// Move the program break to addr, and return where it stands.
void *_Sys_Linux_MoveBreak(void *addr)
{
    return _Sys_x86_64_Linux_InvokeBrk(addr);
}

// Install func as the handler of sig, the old one in old, or return -1.
int _Sys_Linux_SetSignal(int sig, void (*func)(int), void (**old)(int))
{
    if (sig < _SYS_LINUX_SIGNAL_FIRST || sig > _SYS_LINUX_SIGNAL_LAST) {
        _Err_Errno = _SYS_LINUX_EINVAL;
        return -1;
    }
    return (int) _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeRtSigaction(sig, func, _SYS_LINUX_SA_RESTART, 1UL << (sig - _SYS_LINUX_SIGNAL_FIRST), old));
}

// Unblock the signal sig, or return -1 with errno.
int _Sys_Linux_UnblockSignal(int sig)
{
    unsigned long set = 1UL << (sig - _SYS_LINUX_SIGNAL_FIRST);

    return (int) _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeRtSigprocmask(_SYS_LINUX_SIG_UNBLOCK, &set, _SYS_LINUX_NO_SET));
}

// Send the signal sig to the program, or return -1 with errno.
int _Sys_Linux_RaiseSignal(int sig)
{
    return (int) _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeKill(_Sys_x86_64_Linux_InvokeGetpid(), sig));
}

// Read the clock clock into spec, or return -1 with errno.
int _Sys_Linux_ReadClock(int clock, _Sys_Linux_Timespec *spec)
{
    return (int) _Sys_Linux_CheckResult(_Sys_x86_64_Linux_InvokeClockGettime(clock, spec));
}

// End the program, every thread of it, with status.
void _Sys_Linux_ExitProgram(int status)
{
    _Sys_x86_64_Linux_InvokeExitGroup(status);
}

// Return ret, a syscall's result, or -1 with errno for one that is -errno.
long _Sys_Linux_CheckResult(long ret)
{
    if (ret < 0) {
        _Err_Errno = (int) -ret;
        return -1;
    }
    return ret;
}
