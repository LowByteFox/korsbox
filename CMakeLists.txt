# SPDX-License-Identifier: LGPL-3.0-only
# Copyright (c) 2026 LowByteFox
cmake_minimum_required(VERSION 4.0)
project(korsbox C)

include(cmake/libc3c.cmake)

add_executable(korsbox src/main.c src/fetch.c
    src/cc.c src/cxx.c src/env.c
    src/utils/clang.c
    src/targets/windows-x64.c
)
target_link_libraries(korsbox PRIVATE c3c)
