/* SPDX-License-Identifier: LGPL-3.0-only
 * Copyright (c) 2026 LowByteFox
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmd_main)(int argc, char **argv);

int c3c_fakemain();
static void usage();

int fetch_main(int, char**);
int cc_main(int, char**);

struct command {
    const char *name;
    cmd_main main;
} cmds[] = {
    { "fetch-sdk", fetch_main },
    { "cc", cc_main },
    { NULL, NULL }
};

int main(int argc, char **argv)
{
    c3c_fakemain();

    const char *maybe;
    const char *progname = *argv;
    if ((maybe = strrchr(*argv, '/'))) progname = maybe + 1;

    const char *subcmd = NULL;
    if (strcmp(progname, "korsbox") != 0) {
        if (strstr(progname, "korsbox-") != progname) usage();

        subcmd = progname + sizeof("korsbox-") - 1;

        argc--;
        argv++;
    } else {
        if (argc <= 1) usage();

        subcmd = argv[1];
        argc -= 2;
        argv += 2;
    }

    struct command *iter = cmds;
    while (iter->name) {
        if (!strcmp(iter->name, subcmd))
            return iter->main(argc, argv);

        iter++;
    }

    usage();
}

static void usage()
{
    fprintf(stderr, "usage: korsbox command [arg...]\n");
    fprintf(stderr, "commands: ");

    struct command *iter = cmds;
    while (iter->name) {
        fputs(iter->name, stderr);
        fputc(' ', stderr);

        iter++;
    }

    fputc('\n', stderr);


    exit(1);
}
