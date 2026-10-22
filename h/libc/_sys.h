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

// The descriptors of a program's standard input, output and error.
#define _SYS_LINUX_STDIN_FILENO  0
#define _SYS_LINUX_STDOUT_FILENO 1
#define _SYS_LINUX_STDERR_FILENO 2

// Linux's open flags.
#define _SYS_LINUX_O_RDONLY  00
#define _SYS_LINUX_O_WRONLY  01
#define _SYS_LINUX_O_RDWR    02
#define _SYS_LINUX_O_ACCMODE 03
#define _SYS_LINUX_O_CREAT   0100
#define _SYS_LINUX_O_EXCL    0200
#define _SYS_LINUX_O_TRUNC   01000
#define _SYS_LINUX_O_APPEND  02000

// Linux's permission bits for a file's owner, to read and to write.
#define _SYS_LINUX_S_IRUSR 0400
#define _SYS_LINUX_S_IWUSR 0200

// The permissions open asks for a file it creates.
#define _SYS_LINUX_DEFFILEMODE 0666

// Linux's lseek origins.
#define _SYS_LINUX_SEEK_SET 0
#define _SYS_LINUX_SEEK_CUR 1
#define _SYS_LINUX_SEEK_END 2

// Linux's ioctl that reads a terminal's settings, and its control characters.
#define _SYS_LINUX_TCGETS 0x5401
#define _SYS_LINUX_NCCS   19

// Linux's clocks.
#define _SYS_LINUX_CLOCK_REALTIME           0
#define _SYS_LINUX_CLOCK_PROCESS_CPUTIME_ID 2

// Linux's error numbers.
#define _SYS_LINUX_EPERM           1
#define _SYS_LINUX_ENOENT          2
#define _SYS_LINUX_ESRCH           3
#define _SYS_LINUX_EINTR           4
#define _SYS_LINUX_EIO             5
#define _SYS_LINUX_ENXIO           6
#define _SYS_LINUX_E2BIG           7
#define _SYS_LINUX_ENOEXEC         8
#define _SYS_LINUX_EBADF           9
#define _SYS_LINUX_ECHILD          10
#define _SYS_LINUX_EAGAIN          11
#define _SYS_LINUX_ENOMEM          12
#define _SYS_LINUX_EACCES          13
#define _SYS_LINUX_EFAULT          14
#define _SYS_LINUX_ENOTBLK         15
#define _SYS_LINUX_EBUSY           16
#define _SYS_LINUX_EEXIST          17
#define _SYS_LINUX_EXDEV           18
#define _SYS_LINUX_ENODEV          19
#define _SYS_LINUX_ENOTDIR         20
#define _SYS_LINUX_EISDIR          21
#define _SYS_LINUX_EINVAL          22
#define _SYS_LINUX_ENFILE          23
#define _SYS_LINUX_EMFILE          24
#define _SYS_LINUX_ENOTTY          25
#define _SYS_LINUX_ETXTBSY         26
#define _SYS_LINUX_EFBIG           27
#define _SYS_LINUX_ENOSPC          28
#define _SYS_LINUX_ESPIPE          29
#define _SYS_LINUX_EROFS           30
#define _SYS_LINUX_EMLINK          31
#define _SYS_LINUX_EPIPE           32
#define _SYS_LINUX_EDOM            33
#define _SYS_LINUX_ERANGE          34
#define _SYS_LINUX_EDEADLK         35
#define _SYS_LINUX_ENAMETOOLONG    36
#define _SYS_LINUX_ENOLCK          37
#define _SYS_LINUX_ENOSYS          38
#define _SYS_LINUX_ENOTEMPTY       39
#define _SYS_LINUX_ELOOP           40
#define _SYS_LINUX_ENOMSG          42
#define _SYS_LINUX_EIDRM           43
#define _SYS_LINUX_ECHRNG          44
#define _SYS_LINUX_EL2NSYNC        45
#define _SYS_LINUX_EL3HLT          46
#define _SYS_LINUX_EL3RST          47
#define _SYS_LINUX_ELNRNG          48
#define _SYS_LINUX_EUNATCH         49
#define _SYS_LINUX_ENOCSI          50
#define _SYS_LINUX_EL2HLT          51
#define _SYS_LINUX_EBADE           52
#define _SYS_LINUX_EBADR           53
#define _SYS_LINUX_EXFULL          54
#define _SYS_LINUX_ENOANO          55
#define _SYS_LINUX_EBADRQC         56
#define _SYS_LINUX_EBADSLT         57
#define _SYS_LINUX_EBFONT          59
#define _SYS_LINUX_ENOSTR          60
#define _SYS_LINUX_ENODATA         61
#define _SYS_LINUX_ETIME           62
#define _SYS_LINUX_ENOSR           63
#define _SYS_LINUX_ENONET          64
#define _SYS_LINUX_ENOPKG          65
#define _SYS_LINUX_EREMOTE         66
#define _SYS_LINUX_ENOLINK         67
#define _SYS_LINUX_EADV            68
#define _SYS_LINUX_ESRMNT          69
#define _SYS_LINUX_ECOMM           70
#define _SYS_LINUX_EPROTO          71
#define _SYS_LINUX_EMULTIHOP       72
#define _SYS_LINUX_EDOTDOT         73
#define _SYS_LINUX_EBADMSG         74
#define _SYS_LINUX_EOVERFLOW       75
#define _SYS_LINUX_ENOTUNIQ        76
#define _SYS_LINUX_EBADFD          77
#define _SYS_LINUX_EREMCHG         78
#define _SYS_LINUX_ELIBACC         79
#define _SYS_LINUX_ELIBBAD         80
#define _SYS_LINUX_ELIBSCN         81
#define _SYS_LINUX_ELIBMAX         82
#define _SYS_LINUX_ELIBEXEC        83
#define _SYS_LINUX_EILSEQ          84
#define _SYS_LINUX_ERESTART        85
#define _SYS_LINUX_ESTRPIPE        86
#define _SYS_LINUX_EUSERS          87
#define _SYS_LINUX_ENOTSOCK        88
#define _SYS_LINUX_EDESTADDRREQ    89
#define _SYS_LINUX_EMSGSIZE        90
#define _SYS_LINUX_EPROTOTYPE      91
#define _SYS_LINUX_ENOPROTOOPT     92
#define _SYS_LINUX_EPROTONOSUPPORT 93
#define _SYS_LINUX_ESOCKTNOSUPPORT 94
#define _SYS_LINUX_EOPNOTSUPP      95
#define _SYS_LINUX_EPFNOSUPPORT    96
#define _SYS_LINUX_EAFNOSUPPORT    97
#define _SYS_LINUX_EADDRINUSE      98
#define _SYS_LINUX_EADDRNOTAVAIL   99
#define _SYS_LINUX_ENETDOWN        100
#define _SYS_LINUX_ENETUNREACH     101
#define _SYS_LINUX_ENETRESET       102
#define _SYS_LINUX_ECONNABORTED    103
#define _SYS_LINUX_ECONNRESET      104
#define _SYS_LINUX_ENOBUFS         105
#define _SYS_LINUX_EISCONN         106
#define _SYS_LINUX_ENOTCONN        107
#define _SYS_LINUX_ESHUTDOWN       108
#define _SYS_LINUX_ETOOMANYREFS    109
#define _SYS_LINUX_ETIMEDOUT       110
#define _SYS_LINUX_ECONNREFUSED    111
#define _SYS_LINUX_EHOSTDOWN       112
#define _SYS_LINUX_EHOSTUNREACH    113
#define _SYS_LINUX_EALREADY        114
#define _SYS_LINUX_EINPROGRESS     115
#define _SYS_LINUX_ESTALE          116
#define _SYS_LINUX_EUCLEAN         117
#define _SYS_LINUX_ENOTNAM         118
#define _SYS_LINUX_ENAVAIL         119
#define _SYS_LINUX_EISNAM          120
#define _SYS_LINUX_EREMOTEIO       121
#define _SYS_LINUX_EDQUOT          122
#define _SYS_LINUX_ENOMEDIUM       123
#define _SYS_LINUX_EMEDIUMTYPE     124
#define _SYS_LINUX_ECANCELED       125
#define _SYS_LINUX_ENOKEY          126
#define _SYS_LINUX_EKEYEXPIRED     127
#define _SYS_LINUX_EKEYREVOKED     128
#define _SYS_LINUX_EKEYREJECTED    129
#define _SYS_LINUX_EOWNERDEAD      130
#define _SYS_LINUX_ENOTRECOVERABLE 131
#define _SYS_LINUX_ERFKILL         132
#define _SYS_LINUX_EHWPOISON       133

// Linux's first and last signals.
#define _SYS_LINUX_SIGNAL_FIRST 1
#define _SYS_LINUX_SIGNAL_LAST  64

// Linux's sigaction flag that restarts a call a handler interrupted.
#define _SYS_LINUX_SA_RESTART 0x10000000

// Linux's rt_sigprocmask requests.
#define _SYS_LINUX_SIG_UNBLOCK 1

// The words Linux's struct stat on x86-64 ends with and does not use.
#define _SYS_X86_64_LINUX_STAT_UNUSED 3

// Linux's sigaction flag on x86-64 that says the restorer is given.
#define _SYS_X86_64_LINUX_SA_RESTORER 0x04000000

// Linux's struct termios, the kernel's and not glibc's.
typedef struct _Sys_Linux_Termios _Sys_Linux_Termios;
struct _Sys_Linux_Termios {
    unsigned int c_iflag;          // the input modes
    unsigned int c_oflag;          // the output modes
    unsigned int c_cflag;          // the control modes
    unsigned int c_lflag;          // the local modes
    unsigned char c_line;          // the line discipline
    unsigned char c_cc[_SYS_LINUX_NCCS]; // the control characters
};

// Linux's struct timespec.
typedef struct _Sys_Linux_Timespec _Sys_Linux_Timespec;
struct _Sys_Linux_Timespec {
    long tv_sec;  // the seconds
    long tv_nsec; // the nanoseconds past them
};

// Linux's struct stat on x86-64, the kernel's and not glibc's.
typedef struct _Sys_x86_64_Linux_Stat _Sys_x86_64_Linux_Stat;
struct _Sys_x86_64_Linux_Stat {
    unsigned long st_dev;             // the device the file is on
    unsigned long st_ino;             // the file's inode number
    unsigned long st_nlink;           // the hard links to the file
    unsigned int st_mode;             // the file's type and permissions
    unsigned int st_uid;              // the owner's user
    unsigned int st_gid;              // the owner's group
    unsigned int st_pad;              // padding
    unsigned long st_rdev;            // the device a special file stands for
    long st_size;                     // the file's size in bytes
    long st_blksize;                  // the block size best for its I/O
    long st_blocks;                   // the 512-byte blocks it takes up
    unsigned long st_atime;           // the last access, in seconds
    unsigned long st_atime_nsec;      // the last access's nanoseconds
    unsigned long st_mtime;           // the last change of data, in seconds
    unsigned long st_mtime_nsec;      // the last change of data's nanoseconds
    unsigned long st_ctime;           // the last change of status, in seconds
    unsigned long st_ctime_nsec;      // the last change of status's nanoseconds
    long st_unused[_SYS_X86_64_LINUX_STAT_UNUSED]; // unused
};

// Linux's struct sigaction on x86-64, which has a restorer.
typedef struct _Sys_x86_64_Linux_Sigaction _Sys_x86_64_Linux_Sigaction;
struct _Sys_x86_64_Linux_Sigaction {
    void (*sa_handler)(int);   // the handler, or to ignore or the default
    unsigned long sa_flags;    // the flags that change the handling
    void (*sa_restorer)(void); // the function a handler returns through
    unsigned long sa_mask;     // the signals blocked while the handler runs
};

// System calls
long  _Sys_x86_64_Linux_InvokeSyscall(long number, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);
long  _Sys_x86_64_Linux_InvokeRead(int fd, void *buf, unsigned long len);
long  _Sys_x86_64_Linux_InvokeWrite(int fd, const void *buf, unsigned long len);
long  _Sys_x86_64_Linux_InvokeOpen(const char *path, int flags, int mode);
long  _Sys_x86_64_Linux_InvokeClose(int fd);
long  _Sys_x86_64_Linux_InvokeLstat(const char *path, _Sys_x86_64_Linux_Stat *info);
long  _Sys_x86_64_Linux_InvokeLseek(int fd, long offset, int whence);
void *_Sys_x86_64_Linux_InvokeBrk(void *addr);
long  _Sys_x86_64_Linux_InvokeRtSigaction(int sig, void (*func)(int), unsigned long flags, unsigned long mask, void (**old)(int));
long  _Sys_x86_64_Linux_InvokeRtSigprocmask(int how, const unsigned long *set, unsigned long *oset);
long  _Sys_x86_64_Linux_InvokeIoctl(int fd, unsigned long request, void *arg);
long  _Sys_x86_64_Linux_InvokeDup2(int fd, int as);
int   _Sys_x86_64_Linux_InvokeGetpid(void);
long  _Sys_x86_64_Linux_InvokeKill(int pid, int sig);
long  _Sys_x86_64_Linux_InvokeRename(const char *from, const char *to);
long  _Sys_x86_64_Linux_InvokeRmdir(const char *path);
long  _Sys_x86_64_Linux_InvokeUnlink(const char *path);
long  _Sys_x86_64_Linux_InvokeClockGettime(int clock, _Sys_Linux_Timespec *spec);
void  _Sys_x86_64_Linux_InvokeExitGroup(int status);

// Signal handlers
void _Sys_x86_64_Linux_InvokeRtSigreturn(void);

// Files
long  _Sys_Linux_ReadFile(int fd, void *buf, unsigned long len);
long  _Sys_Linux_WriteFile(int fd, const void *buf, unsigned long len);
int   _Sys_Linux_OpenFile(const char *path, int flags, int mode);
int   _Sys_Linux_CloseFile(int fd);
long  _Sys_Linux_SeekFile(int fd, long offset, int whence);
int   _Sys_Linux_CopyDescriptor(int fd, int as);
_Bool _Sys_Linux_IsTerminal(int fd);

// Names
int   _Sys_Linux_RemoveFile(const char *path);
int   _Sys_Linux_RenameFile(const char *from, const char *to);
_Bool _Sys_Linux_IsNameUnused(const char *path);

// Memory
void *_Sys_Linux_MoveBreak(void *addr);

// Signals
int _Sys_Linux_SetSignal(int sig, void (*func)(int), void (**old)(int));
int _Sys_Linux_UnblockSignal(int sig);
int _Sys_Linux_RaiseSignal(int sig);

// Time
int _Sys_Linux_ReadClock(int clock, _Sys_Linux_Timespec *spec);

// Exit
void _Sys_Linux_ExitProgram(int status);

// Results
long _Sys_Linux_CheckResult(long ret);

#endif // _SYS_H
