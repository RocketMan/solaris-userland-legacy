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
 * Copyright (c) 2022-2023 Jim Mason <jmason@ibinx.com>
 *
 * This file contains static shims for rust.
 */

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


/**
 * shim for dup3(2)
 */
int dup3(int oldfd, int newfd, int flags) {
  if (flags & ~O_CLOEXEC || newfd == oldfd)
    return EINVAL;

  return fcntl(oldfd, flags & O_CLOEXEC ? F_DUP2FD_CLOEXEC : F_DUP2FD, newfd);
}

/**
 * shim for pipe2(2)
 */
int pipe2(int fd[2], int flags) {
  int ret = pipe(fd);

  if (!flags || ret) return ret;

  if (flags & O_CLOEXEC) {
    fcntl(fd[0], F_SETFD, FD_CLOEXEC);
    fcntl(fd[1], F_SETFD, FD_CLOEXEC);
  }

  if (flags & O_NONBLOCK) {
    fcntl(fd[0], F_SETFL, O_NONBLOCK);
    fcntl(fd[1], F_SETFL, O_NONBLOCK);
  }

  return 0;
}
