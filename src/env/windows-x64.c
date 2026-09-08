/* SPDX-License-Identifier: LGPL-3.0-only
 * Copyright (c) 2026 LowByteFox
 */
#include <stdio.h>

int env_windows_x64_main(enum env_type type, FILE *out)
{
    fprintf(out, "set(CMAKE_SYSTEM_NAME Windows)\n"
                 "set(CMAKE_SYSTEM_PROCESSOR x86_64)\n\n"
    );

    fprintf(out, "set(CMAKE_C_COMPILER \"korsbox\")\n"
                 "set(CMAKE_C_COMPILER_ARG1 \"cc\")\n"
                 "set(CMAKE_C_FLAGS_INIT \"-t windows-x64\")\n\n"
    );

    fprintf(out, "set(CMAKE_CXX_COMPILER \"korsbox\")\n"
                 "set(CMAKE_CXX_COMPILER_ARG1 \"c++\")\n"
                 "set(CMAKE_CXX_FLAGS_INIT \"-t windows-x64\")\n\n"
    );

    fprintf(out, "set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)\n"
                 "set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)\n"
                 "set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)\n\n"
    );

    fprintf(out, "if(NOT CMAKE_MAKE_PROGRAM)\n"
                 "    if(CMAKE_GENERATOR MATCHES \"Ninja\")\n"
                 "        find_program(CMAKE_MAKE_PROGRAM ninja)\n"
                 "    elseif(CMAKE_GENERATOR MATCHES \"Unix Makefiles\")\n"
                 "        find_program(CMAKE_MAKE_PROGRAM make)\n"
                 "    endif()\n"
                 "endif()\n"
    );

    return 0;
}
