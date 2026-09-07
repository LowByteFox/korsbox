# SPDX-License-Identifier: LGPL-3.0-or-later
# Copyright (c) 2026 LowByteFox
if(POLICY CMP0169)
  cmake_policy(SET CMP0169 OLD)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(CURL REQUIRED IMPORTED_TARGET libcurl)

include(FetchContent)
FetchContent_Declare(
    c3c
    URL https://github.com/c3lang/c3c/archive/refs/heads/master.zip
)

FetchContent_GetProperties(c3c)
if(NOT c3c_POPULATED)
    FetchContent_Populate(c3c)
endif()

set(C3C_SOURCES
    ${c3c_SOURCE_DIR}/src/utils/fetch_sdk/macos_sdk.c
    ${c3c_SOURCE_DIR}/src/utils/cpio.c
    ${c3c_SOURCE_DIR}/src/utils/file_utils.c
    ${c3c_SOURCE_DIR}/src/utils/byte_buffer.c
    ${c3c_SOURCE_DIR}/src/utils/http.c
    ${c3c_SOURCE_DIR}/src/utils/malloc.c
    ${c3c_SOURCE_DIR}/src/utils/errors.c
    ${c3c_SOURCE_DIR}/src/utils/whereami.c
    ${c3c_SOURCE_DIR}/src/utils/pbzx.c
    ${c3c_SOURCE_DIR}/src/utils/stringutils.c
    ${c3c_SOURCE_DIR}/src/utils/sucatalog.c
    ${c3c_SOURCE_DIR}/src/utils/vmem.c
    ${c3c_SOURCE_DIR}/src/utils/xar.c
    ${c3c_SOURCE_DIR}/src/utils/xz_stream.c
    ${c3c_SOURCE_DIR}/dependencies/xz/standalone.c
    ${c3c_SOURCE_DIR}/dependencies/miniz/miniz.c
    ${c3c_SOURCE_DIR}/dependencies/miniz/zlib_compat.c
    ${c3c_SOURCE_DIR}/src/utils/fetch_sdk/windows_sdk.c
    ${c3c_SOURCE_DIR}/src/utils/json.c
    ${c3c_SOURCE_DIR}/src/utils/unzipper.c
    ${c3c_SOURCE_DIR}/src/utils/msi.c
    ../c3c_stubs/main.c
    ../c3c_stubs/fetch_utils.c
    ../c3c_stubs/compiler.c
)

add_library(c3c STATIC ${C3C_SOURCES})
target_include_directories(c3c PUBLIC
    ${c3c_SOURCE_DIR}/src
    ${c3c_SOURCE_DIR}/src/utils
    ${c3c_SOURCE_DIR}/src/utils/fetch_sdk
    ${c3c_SOURCE_DIR}/dependencies/xz
    ${c3c_SOURCE_DIR}/dependencies/miniz
)
target_compile_definitions(c3c PRIVATE
    C3_LINK_CURL
)
target_link_libraries(c3c PRIVATE PkgConfig::CURL)
