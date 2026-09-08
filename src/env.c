/* SPDX-License-Identifier: LGPL-3.0-only
 * Copyright (c) 2026 LowByteFox
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum env_type {
    ENV_UNKNOWN,
    ENV_CMAKE,
    ENV_MESON, /* not yet */
    ENV_INVALID
};

static void usage();
static void print_targets();
static void print_build_systems();
static enum env_type find_env(const char *name);

typedef int (*recipe)(enum env_type, FILE*);

#include "env/windows-x64.c"

static struct build {
    const char *name;
    enum env_type type;
} systems[] = {
    { "cmake", ENV_CMAKE },
    { NULL, ENV_INVALID }
};

static struct env {
    const char *name;
    recipe main;
} targets[] = {
    { "windows-x64", env_windows_x64_main },
    { NULL, NULL }
};

int env_main(int argc, char **argv)
{
    FILE *out = stdout;
    const char *target = NULL;
    enum env_type env = ENV_UNKNOWN;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-l")) {
            printf("available build systems:\n");
            print_build_systems();
            printf("available targets:\n");
            print_targets();
            return 0;
        } else if (!strcmp(argv[i], "-t") && i + 1 < argc) {
            target = argv[i + 1];
            i++;
        } else if (!strcmp(argv[i], "-b") && i + 1 < argc) {
            env = find_env(argv[i + 1]);
            if (env == ENV_INVALID) {
                fprintf(stderr, "error: invalid build system \"%s\"\n",
                    argv[i + 1]);
                return 1;
            }

            i++;
        }
    }

    if (!target || env == ENV_UNKNOWN) usage();

    const struct env *iter = targets;
    while (iter->name) {
        if (!strcmp(iter->name, target)) break;
        iter++;
    }

    if (!iter->name) {
        fprintf(stderr, "error: unknown target \"%s\"\n", target);
        return 1;
    }

    return iter->main(env, out);
}

static enum env_type find_env(const char *name)
{
    const struct build *iter = systems;
    while (iter->name) {
        if (!strcmp(iter->name, name))
            return iter->type;

        iter++;
    }

    return iter->type;
}

static void print_build_systems()
{
    const struct build *iter = systems;
    while (iter->name) {
        printf("  %s\n", iter->name);
        iter++;
    }
}

static void print_targets()
{
    const struct env *iter = targets;
    while (iter->name) {
        printf("  %s\n", iter->name);
        iter++;
    }
}

static void usage()
{
    fprintf(stderr, "usage: korsbox env [-l] [-o out] -b system -t target file\n"
                    "options:\n"
                    "  -b     build system to generate toolchain file for\n"
                    "  -l     list all build systems, OS and architecture targets\n"
                    "  -o     specify output file\n"
                    "  -t     compile for a particular OS target + architecture\n");
    exit(1);
}
