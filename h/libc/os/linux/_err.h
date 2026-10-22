/*
 * C header file for the texts a running program prints on Linux.
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

#ifndef _OS_LINUX_ERR_H
#define _OS_LINUX_ERR_H

// The error numbers strerror's table holds, from 0 to Linux's last.
#define _ERR_LINUX_ERRNO_COUNT 134

// strerror's texts for the error numbers, glibc's for every one Linux names.
#define _ERR_LINUX_ERRNO_SUCCESS         "Success"
#define _ERR_LINUX_ERRNO_EPERM           "Operation not permitted"
#define _ERR_LINUX_ERRNO_ENOENT          "No such file or directory"
#define _ERR_LINUX_ERRNO_ESRCH           "No such process"
#define _ERR_LINUX_ERRNO_EINTR           "Interrupted system call"
#define _ERR_LINUX_ERRNO_EIO             "Input/output error"
#define _ERR_LINUX_ERRNO_ENXIO           "No such device or address"
#define _ERR_LINUX_ERRNO_E2BIG           "Argument list too long"
#define _ERR_LINUX_ERRNO_ENOEXEC         "Exec format error"
#define _ERR_LINUX_ERRNO_EBADF           "Bad file descriptor"
#define _ERR_LINUX_ERRNO_ECHILD          "No child processes"
#define _ERR_LINUX_ERRNO_EAGAIN          "Resource temporarily unavailable"
#define _ERR_LINUX_ERRNO_ENOMEM          "Cannot allocate memory"
#define _ERR_LINUX_ERRNO_EACCES          "Permission denied"
#define _ERR_LINUX_ERRNO_EFAULT          "Bad address"
#define _ERR_LINUX_ERRNO_ENOTBLK         "Block device required"
#define _ERR_LINUX_ERRNO_EBUSY           "Device or resource busy"
#define _ERR_LINUX_ERRNO_EEXIST          "File exists"
#define _ERR_LINUX_ERRNO_EXDEV           "Invalid cross-device link"
#define _ERR_LINUX_ERRNO_ENODEV          "No such device"
#define _ERR_LINUX_ERRNO_ENOTDIR         "Not a directory"
#define _ERR_LINUX_ERRNO_EISDIR          "Is a directory"
#define _ERR_LINUX_ERRNO_EINVAL          "Invalid argument"
#define _ERR_LINUX_ERRNO_ENFILE          "Too many open files in system"
#define _ERR_LINUX_ERRNO_EMFILE          "Too many open files"
#define _ERR_LINUX_ERRNO_ENOTTY          "Inappropriate ioctl for device"
#define _ERR_LINUX_ERRNO_ETXTBSY         "Text file busy"
#define _ERR_LINUX_ERRNO_EFBIG           "File too large"
#define _ERR_LINUX_ERRNO_ENOSPC          "No space left on device"
#define _ERR_LINUX_ERRNO_ESPIPE          "Illegal seek"
#define _ERR_LINUX_ERRNO_EROFS           "Read-only file system"
#define _ERR_LINUX_ERRNO_EMLINK          "Too many links"
#define _ERR_LINUX_ERRNO_EPIPE           "Broken pipe"
#define _ERR_LINUX_ERRNO_EDOM            "Numerical argument out of domain"
#define _ERR_LINUX_ERRNO_ERANGE          "Numerical result out of range"
#define _ERR_LINUX_ERRNO_EDEADLK         "Resource deadlock avoided"
#define _ERR_LINUX_ERRNO_ENAMETOOLONG    "File name too long"
#define _ERR_LINUX_ERRNO_ENOLCK          "No locks available"
#define _ERR_LINUX_ERRNO_ENOSYS          "Function not implemented"
#define _ERR_LINUX_ERRNO_ENOTEMPTY       "Directory not empty"
#define _ERR_LINUX_ERRNO_ELOOP           "Too many levels of symbolic links"
#define _ERR_LINUX_ERRNO_ENOMSG          "No message of desired type"
#define _ERR_LINUX_ERRNO_EIDRM           "Identifier removed"
#define _ERR_LINUX_ERRNO_ECHRNG          "Channel number out of range"
#define _ERR_LINUX_ERRNO_EL2NSYNC        "Level 2 not synchronized"
#define _ERR_LINUX_ERRNO_EL3HLT          "Level 3 halted"
#define _ERR_LINUX_ERRNO_EL3RST          "Level 3 reset"
#define _ERR_LINUX_ERRNO_ELNRNG          "Link number out of range"
#define _ERR_LINUX_ERRNO_EUNATCH         "Protocol driver not attached"
#define _ERR_LINUX_ERRNO_ENOCSI          "No CSI structure available"
#define _ERR_LINUX_ERRNO_EL2HLT          "Level 2 halted"
#define _ERR_LINUX_ERRNO_EBADE           "Invalid exchange"
#define _ERR_LINUX_ERRNO_EBADR           "Invalid request descriptor"
#define _ERR_LINUX_ERRNO_EXFULL          "Exchange full"
#define _ERR_LINUX_ERRNO_ENOANO          "No anode"
#define _ERR_LINUX_ERRNO_EBADRQC         "Invalid request code"
#define _ERR_LINUX_ERRNO_EBADSLT         "Invalid slot"
#define _ERR_LINUX_ERRNO_EBFONT          "Bad font file format"
#define _ERR_LINUX_ERRNO_ENOSTR          "Device not a stream"
#define _ERR_LINUX_ERRNO_ENODATA         "No data available"
#define _ERR_LINUX_ERRNO_ETIME           "Timer expired"
#define _ERR_LINUX_ERRNO_ENOSR           "Out of streams resources"
#define _ERR_LINUX_ERRNO_ENONET          "Machine is not on the network"
#define _ERR_LINUX_ERRNO_ENOPKG          "Package not installed"
#define _ERR_LINUX_ERRNO_EREMOTE         "Object is remote"
#define _ERR_LINUX_ERRNO_ENOLINK         "Link has been severed"
#define _ERR_LINUX_ERRNO_EADV            "Advertise error"
#define _ERR_LINUX_ERRNO_ESRMNT          "Srmount error"
#define _ERR_LINUX_ERRNO_ECOMM           "Communication error on send"
#define _ERR_LINUX_ERRNO_EPROTO          "Protocol error"
#define _ERR_LINUX_ERRNO_EMULTIHOP       "Multihop attempted"
#define _ERR_LINUX_ERRNO_EDOTDOT         "RFS specific error"
#define _ERR_LINUX_ERRNO_EBADMSG         "Bad message"
#define _ERR_LINUX_ERRNO_EOVERFLOW       "Value too large for defined data type"
#define _ERR_LINUX_ERRNO_ENOTUNIQ        "Name not unique on network"
#define _ERR_LINUX_ERRNO_EBADFD          "File descriptor in bad state"
#define _ERR_LINUX_ERRNO_EREMCHG         "Remote address changed"
#define _ERR_LINUX_ERRNO_ELIBACC         "Can not access a needed shared library"
#define _ERR_LINUX_ERRNO_ELIBBAD         "Accessing a corrupted shared library"
#define _ERR_LINUX_ERRNO_ELIBSCN         ".lib section in a.out corrupted"
#define _ERR_LINUX_ERRNO_ELIBMAX         "Attempting to link in too many shared libraries"
#define _ERR_LINUX_ERRNO_ELIBEXEC        "Cannot exec a shared library directly"
#define _ERR_LINUX_ERRNO_EILSEQ          "Invalid or incomplete multibyte or wide character"
#define _ERR_LINUX_ERRNO_ERESTART        "Interrupted system call should be restarted"
#define _ERR_LINUX_ERRNO_ESTRPIPE        "Streams pipe error"
#define _ERR_LINUX_ERRNO_EUSERS          "Too many users"
#define _ERR_LINUX_ERRNO_ENOTSOCK        "Socket operation on non-socket"
#define _ERR_LINUX_ERRNO_EDESTADDRREQ    "Destination address required"
#define _ERR_LINUX_ERRNO_EMSGSIZE        "Message too long"
#define _ERR_LINUX_ERRNO_EPROTOTYPE      "Protocol wrong type for socket"
#define _ERR_LINUX_ERRNO_ENOPROTOOPT     "Protocol not available"
#define _ERR_LINUX_ERRNO_EPROTONOSUPPORT "Protocol not supported"
#define _ERR_LINUX_ERRNO_ESOCKTNOSUPPORT "Socket type not supported"
#define _ERR_LINUX_ERRNO_EOPNOTSUPP      "Operation not supported"
#define _ERR_LINUX_ERRNO_EPFNOSUPPORT    "Protocol family not supported"
#define _ERR_LINUX_ERRNO_EAFNOSUPPORT    "Address family not supported by protocol"
#define _ERR_LINUX_ERRNO_EADDRINUSE      "Address already in use"
#define _ERR_LINUX_ERRNO_EADDRNOTAVAIL   "Cannot assign requested address"
#define _ERR_LINUX_ERRNO_ENETDOWN        "Network is down"
#define _ERR_LINUX_ERRNO_ENETUNREACH     "Network is unreachable"
#define _ERR_LINUX_ERRNO_ENETRESET       "Network dropped connection on reset"
#define _ERR_LINUX_ERRNO_ECONNABORTED    "Software caused connection abort"
#define _ERR_LINUX_ERRNO_ECONNRESET      "Connection reset by peer"
#define _ERR_LINUX_ERRNO_ENOBUFS         "No buffer space available"
#define _ERR_LINUX_ERRNO_EISCONN         "Transport endpoint is already connected"
#define _ERR_LINUX_ERRNO_ENOTCONN        "Transport endpoint is not connected"
#define _ERR_LINUX_ERRNO_ESHUTDOWN       "Cannot send after transport endpoint shutdown"
#define _ERR_LINUX_ERRNO_ETOOMANYREFS    "Too many references: cannot splice"
#define _ERR_LINUX_ERRNO_ETIMEDOUT       "Connection timed out"
#define _ERR_LINUX_ERRNO_ECONNREFUSED    "Connection refused"
#define _ERR_LINUX_ERRNO_EHOSTDOWN       "Host is down"
#define _ERR_LINUX_ERRNO_EHOSTUNREACH    "No route to host"
#define _ERR_LINUX_ERRNO_EALREADY        "Operation already in progress"
#define _ERR_LINUX_ERRNO_EINPROGRESS     "Operation now in progress"
#define _ERR_LINUX_ERRNO_ESTALE          "Stale file handle"
#define _ERR_LINUX_ERRNO_EUCLEAN         "Structure needs cleaning"
#define _ERR_LINUX_ERRNO_ENOTNAM         "Not a XENIX named type file"
#define _ERR_LINUX_ERRNO_ENAVAIL         "No XENIX semaphores available"
#define _ERR_LINUX_ERRNO_EISNAM          "Is a named type file"
#define _ERR_LINUX_ERRNO_EREMOTEIO       "Remote I/O error"
#define _ERR_LINUX_ERRNO_EDQUOT          "Disk quota exceeded"
#define _ERR_LINUX_ERRNO_ENOMEDIUM       "No medium found"
#define _ERR_LINUX_ERRNO_EMEDIUMTYPE     "Wrong medium type"
#define _ERR_LINUX_ERRNO_ECANCELED       "Operation canceled"
#define _ERR_LINUX_ERRNO_ENOKEY          "Required key not available"
#define _ERR_LINUX_ERRNO_EKEYEXPIRED     "Key has expired"
#define _ERR_LINUX_ERRNO_EKEYREVOKED     "Key has been revoked"
#define _ERR_LINUX_ERRNO_EKEYREJECTED    "Key was rejected by service"
#define _ERR_LINUX_ERRNO_EOWNERDEAD      "Owner died"
#define _ERR_LINUX_ERRNO_ENOTRECOVERABLE "State not recoverable"
#define _ERR_LINUX_ERRNO_ERFKILL         "Operation not possible due to RF-kill"
#define _ERR_LINUX_ERRNO_EHWPOISON       "Memory page has hardware error"

#endif // _OS_LINUX_ERR_H
