/*
run-time cpu feature detection code
mm, alphabet soup...

Glenn Kennard <d98gk@efd.lth.se>
*/

#include "fitz-base.h"

/* global run-time constant */
unsigned fz_cpuflags = 0;

#ifndef HAVE_CPUDEP

void fz_accelerate(void) {}

void fz_cpudetect(void) {}

#else

#include <signal.h> /* signal/sigaction */
#include <setjmp.h> /* sigsetjmp/siglongjmp */

typedef struct {
    void (*test)(void);
    const unsigned flag;
    const char*    name;
} featuretest;

static sigjmp_buf            jmpbuf;
static volatile sig_atomic_t canjump;

static void sigillhandler(int sig)
{
    if (!canjump) {
        signal(sig, SIG_DFL);
        raise(sig);
    }

    canjump = 0;
    siglongjmp(jmpbuf, 1);
}

static int enabled(char* env, const char* ext)
{
    int   len;
    char* s;
    if (!env)
        return 1;
    len = strlen(ext);
    while ((s = strstr(env, ext))) {
        s += len;
        if (*s == ' ' || *s == ',' || *s == '\0')
            return 1;
    }
    return 0;
}

static void dumpflags(void)
{
    unsigned f = fz_cpuflags;
    int      i, n;

    fputs("detected cpu features:", stdout);
    n = 0;
    for (i = 0; i < sizeof(features) / sizeof(featuretest); i++) {
        if (f & features[i].flag) {
            fputc(' ', stdout);
            fputs(features[i].name, stdout);
            n++;
        }
    }
    if (!n)
        fputs(" none", stdout);
    fputc('\n', stdout);
}

void fz_cpudetect(void)
{
    static int hasrun = 0;

    unsigned flags = 0;
    int      i;
    void (*oldhandler)(int) = NULL;
    void (*tmphandler)(int);
    char* env;

    if (hasrun)
        return;
    hasrun = 1;

    env = getenv("CPUACCEL");

    for (i = 0; i < sizeof(features) / sizeof(featuretest); i++) {
        canjump = 0;

        tmphandler = signal(SIGILL, sigillhandler);
        if (!oldhandler)
            oldhandler = tmphandler;

        if (sigsetjmp(jmpbuf, 1)) {
            /* test failed - disable feature */
            flags &= ~features[i].flag;
            continue;
        }

        canjump = 1;

        features[i].test();

        /* if we got here the test succeeded */
        if (enabled(env, features[i].name))
            flags |= features[i].flag;
        else
            flags &= ~features[i].flag;
    }

    /* restore previous signal handler */
    signal(SIGILL, oldhandler);

    fz_cpuflags = flags;

    dumpflags();
}

static __attribute__((constructor, used)) void fzcpudetect(void) { fz_cpudetect(); }

#endif
