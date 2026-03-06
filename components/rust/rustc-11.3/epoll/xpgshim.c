/* solaris_xpg_shim.c */

#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <pthread.h>

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
