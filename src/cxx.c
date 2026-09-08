/* SPDX-License-Identifier: LGPL-3.0-only
 * Copyright (c) 2026 LowByteFox
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static void usage();
static void print_targets();

typedef int (*tgt_main)(int argc, char **argv, bool);

int target_windows_x64_main(int, char**, bool);

static struct tgt {
    const char *name;
    tgt_main main;
} targets[] = {
    { "windows-x64", target_windows_x64_main },
    { NULL, NULL }
};

int cxx_main(int argc, char **argv)
{
    const char *target = NULL;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-l")) {
            printf("available targets:\n");
            print_targets();
            return 0;
        } else if (!strcmp(argv[i], "-t") && i + 1 < argc) {
            target = argv[i + 1];
            argc -= i + 2;
            argv += i + 2;
            break;
        }
    }

    if (!target) usage();

    const struct tgt *iter = targets;
    while (iter->name) {
        if (!strcmp(iter->name, target)) break;
        iter++;
    }

    if (!iter->name) {
        fprintf(stderr, "error: unknown target \"%s\"\n", target);
        return 1;
    }

    return iter->main(argc, argv, true);
}

static void print_targets()
{
    const struct tgt *iter = targets;
    while (iter->name) {
        printf("  %s\n", iter->name);
        iter++;
    }
}

static void usage()
{
    fprintf(stderr, "usage: korsbox cxx [-l] -t target [clang++_arg...]\n"
                    "options:\n"
                    "  -l     list all OS and architecture targets\n"
                    "  -t     compile for a particular OS target + architecture\n");
    exit(1);
}
