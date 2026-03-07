/**
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 *
 * Copyright (c) 2022-2026 Jim Mason <jmason@ibinx.com>
 *
 * This file contains shims for rust libc on Solaris 11.3.
 */

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>

/*
 * Rust crates (via libc) may expect these XPG entry points.
 * Solaris 11.3 exposes the underlying functions but not
 * the redirected symbol names, so we provide thin wrappers.
 *
 * Build with:
 *
 *    clang -fPIC -shared -o libxpgshim.so xpgshim.c
 */

/* XPG4 hardlink entry point */
int __link_xpg4(const char *src, const char *dst)
{
    return link(src, dst);
}

/* XPG7 sysconf entry point */
long __sysconf_xpg7(int name)
{
    return sysconf(name);
}

/*
 * XNET7 socket entry point.
 * On Solaris 11.3 the real symbol is __xnet_socket.
 */
extern int __xnet_socket(int domain, int type, int protocol);

int __xnet7_socket(int domain, int type, int protocol)
{
    return __xnet_socket(domain, type, protocol);
}

/* XPG7 pthread_kill entry point */
int __pthread_kill_xpg7(pthread_t thread, int sig)
{
    return pthread_kill(thread, sig);
}

/*
 * The following are small compatiblity shims for certain
 * functions which do not exist on Solaris 11.3, but are
 * expected by rust's libc crate.
 */

/* shim for dup3(2) */
int dup3(int oldfd, int newfd, int flags)
{
  if (flags & ~O_CLOEXEC || newfd == oldfd) {
    errno = EINVAL;
    return -1;
  }

  if (newfd < 0) {
    errno = EBADF;
    return -1;
  }

  return fcntl(oldfd, flags & O_CLOEXEC ? F_DUP2FD_CLOEXEC : F_DUP2FD, newfd);
}

/* shim for pipe2(2) */
int pipe2(int fd[2], int flags)
{
  if (flags & ~(O_CLOEXEC | O_NONBLOCK)) {
    errno = EINVAL;
    return -1;
  }

  if (pipe(fd) < 0)
    return -1;

  if (flags & O_CLOEXEC) {
    if (fcntl(fd[0], F_SETFD, FD_CLOEXEC) < 0 ||
        fcntl(fd[1], F_SETFD, FD_CLOEXEC) < 0)
      goto fail;
  }

  if (flags & O_NONBLOCK) {
    int f;

    f = fcntl(fd[0], F_GETFL);
    if (f < 0 || fcntl(fd[0], F_SETFL, f | O_NONBLOCK) < 0)
      goto fail;

    f = fcntl(fd[1], F_GETFL);
    if (f < 0 || fcntl(fd[1], F_SETFL, f | O_NONBLOCK) < 0)
      goto fail;
  }

  return 0;

fail:
  close(fd[0]);
  close(fd[1]);
  return -1;
}

/*
 * SOCK_CLOEXEC and SOCK_NONBLOCK match the values defined in
 * the libc file src/unix/solarish/mod.rs.
 */
#ifndef SOCK_CLOEXEC
#define SOCK_CLOEXEC 0x080000
#endif
#ifndef SOCK_NONBLOCK
#define SOCK_NONBLOCK 0x100000
#endif

/* shim for accept4(2) */
int accept4(int sockfd, struct sockaddr *addr,
            socklen_t *addrlen, int flags)
{
  if (flags & ~(SOCK_CLOEXEC | SOCK_NONBLOCK)) {
    errno = EINVAL;
    return -1;
  }

  int fd = accept(sockfd, addr, addrlen);
  if (fd < 0)
    return -1;

  if (flags & SOCK_CLOEXEC)
    fcntl(fd, F_SETFD, FD_CLOEXEC);

  if (flags & SOCK_NONBLOCK) {
    int f = fcntl(fd, F_GETFL);
    if (f >= 0)
      fcntl(fd, F_SETFL, f | O_NONBLOCK);
  }

  return fd;
}
