/* SPDX-License-Identifier: LGPL-3.0-only
 * Copyright (c) 2026 LowByteFox
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <build/build.h>

static void usage();

int fetch_main(int argc, char **argv)
{
    if (argc == 0) usage();
    BuildOptions options = { 0 };
    options.msvc_fetch_headers = true;

    for (int i = 0; i < argc - 1; i++) {
        if (!strcmp(argv[i], "-a"))
            options.fetch_accept_license = true;
    }

    const char *os = argv[argc - 1];

    switch (os[0]) {
    case 'a':
    case 'm':
        if (!strcmp(os, "msvc")) goto windows;
        if (!strcmp(os, "apple") || !strcmp(os, "mac") || !strcmp(os, "macos"))
            goto macos;

        usage();
macos:
        fetch_macsdk(&options);
        break;
    case 'w':
        if (!strcmp(os, "win") || !strcmp(os, "windows")) goto windows;

        usage();
windows:
        fetch_winsdk(&options);
        break;
    }

    return 0;
}

static void usage()
{
    fprintf(stderr, "usage: korsbox fetch-sdk [-a] target\n"
                    "target: apple mac macos msvc win windows\n"
                    "options:\n"
                    "  -a     accept license\n");
    exit(1);
}
