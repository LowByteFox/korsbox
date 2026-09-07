/* SPDX-License-Identifier: LGPL-3.0-or-later
 * Copyright (c) 2019 Christoffer Lerno
 * Copyright (c) 2026 LowByteFox
 */
#include <stdio.h>
#include <stdbool.h>

#ifndef _WIN32
#include <unistd.h>
#endif

bool use_ansi(void)
{
#ifdef _WIN32
    return false;
#else
    return isatty(fileno(stdout));
#endif
}
