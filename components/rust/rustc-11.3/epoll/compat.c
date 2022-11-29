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
 * Copyright (c) 2022 Jim Mason <jmason@ibinx.com>
 *
 * This file contains static shims for rust.
 */

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#undef LOCK_SH
#define LOCK_SH 1
#undef LOCK_EX
#define LOCK_EX 2
#undef LOCK_NB
#define LOCK_NB 4
#undef LOCK_UN
#define LOCK_UN 8

/**
 * shim for flock(2)
 *
 * source: https://www.perkin.org.uk/posts/solaris-portability-flock.html
 */
int flock(int fd, int op) {
  int rc = 0;

#if defined(F_SETLK) && defined(F_SETLKW)
  struct flock fl = {0};

  switch (op & (LOCK_EX|LOCK_SH|LOCK_UN)) {
  case LOCK_EX:
    fl.l_type = F_WRLCK;
    break;

  case LOCK_SH:
    fl.l_type = F_RDLCK;
    break;

  case LOCK_UN:
    fl.l_type = F_UNLCK;
    break;

  default:
    errno = EINVAL;
    return -1;
  }

  fl.l_whence = SEEK_SET;
  rc = fcntl(fd, op & LOCK_NB ? F_SETLK : F_SETLKW, &fl);

  if (rc && (errno == EAGAIN))
    errno = EWOULDBLOCK;
#endif

  return rc;
}
