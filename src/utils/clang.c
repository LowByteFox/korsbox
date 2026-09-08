/* SPDX-License-Identifier: LGPL-3.0-only
 * Copyright (c) 2026 LowByteFox
 */
#include <stdio.h>

#include <utils/lib.h>

char *clang_get_resources()
{
    return execute_cmd("clang -print-resource-dir", false, NULL, 256);
}
