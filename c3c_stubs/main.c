/* SPDX-License-Identifier: LGPL-3.0-only
 * Copyright (c) 2026 LowByteFox
 */
#include <stdbool.h>
#include <setjmp.h>
#include <build/build.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

bool debug_log = false;
jmp_buf on_error_jump;
const char *compiler_exe_name;

void exit_compiler(int exit_value)
{
    longjmp(on_error_jump, exit_value);
}

static void cleanup()
{
    memory_release();
}

int c3c_fakemain()
{
    srand((unsigned int) time(NULL));
    compiler_exe_name = "korsbox";
#ifdef __OpenBSD__
    // override data size constrain set up by the system */
    struct rlimit l;
    getrlimit(RLIMIT_DATA, &l);
    l.rlim_cur = l.rlim_max;
    setrlimit(RLIMIT_DATA, &l);
#endif
#if PLATFORM_WINDOWS
    // Set the console input and output codepage to utf8 to handle utf8 text correctly
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    
    // Setjmp will allow us to add things like fuzzing with
    // easy restarts.
    int result = setjmp(on_error_jump);
    if (result)
    {
        cleanup();
        if (result == COMPILER_SUCCESS_EXIT) result = EXIT_SUCCESS;
        return result;
    }
    
    memory_init(0);
    
    return 0;
}
