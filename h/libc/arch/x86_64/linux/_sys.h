/*
 * C header file for the system layer's layouts on x86-64 Linux.
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

#ifndef _ARCH_X86_64_LINUX_SYS_H
#define _ARCH_X86_64_LINUX_SYS_H

// The words Linux's struct stat on x86-64 ends with and does not use.
#define _SYS_X86_64_LINUX_STAT_UNUSED 3

// Linux's sigaction flag on x86-64 that says the restorer is given.
#define _SYS_X86_64_LINUX_SA_RESTORER 0x04000000

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

// Signal handlers
void _Sys_x86_64_Linux_InvokeRtSigreturn(void);

#endif // _ARCH_X86_64_LINUX_SYS_H
