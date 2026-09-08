/* SPDX-License-Identifier: LGPL-3.0-only
 * Copyright (c) 2026 LowByteFox
 */
#include <unistd.h>

#include <utils/lib.h>

char *get_cache_output_path(const char *subdir);
char *clang_get_resources();

int target_windows_x64_main(int argc, char **argv, bool is_cpp)
{
    const char *sdk = get_cache_output_path("msvc_sdk");
    char *inc_root = file_append_path(sdk, "include");
    char *sdk_inc_root = file_append_path(inc_root, "x64");
    char *sdk_root = file_append_path(sdk, "x64");

    char *clang_res = clang_get_resources();
    char **clang_args = VECNEW(char*, 32 + argc);

    vec_add(clang_args, is_cpp ? "clang++" : "clang");
    vec_add(clang_args, "--target=x86_64-pc-windows-msvc");
    vec_add(clang_args, "-fuse-ld=lld");
    vec_add(clang_args, "-fms-extensions");
    vec_add(clang_args, "-fms-compatibility");
    vec_add(clang_args, "-fcolor-diagnostics");
    vec_add(clang_args, "-Wno-nonportable-include-path");
    vec_add(clang_args, "-Wno-ignored-attributes");
    vec_add(clang_args, "-Wno-pragma-pack");
    vec_add(clang_args, "-Wno-deprecated-declarations");
    vec_add(clang_args, "-D_CRT_SECURE_NO_WARNINGS");
    vec_add(clang_args, "-D_CRT_NONSTDC_NO_WARNINGS");
    vec_add(clang_args, "-D_AMD64_");
    vec_add(clang_args, "-isystem");
    vec_add(clang_args, file_append_path(clang_res, "include"));
    vec_add(clang_args, "-isystem");
    vec_add(clang_args, file_append_path(inc_root, "crt"));
    vec_add(clang_args, "-isystem");
    vec_add(clang_args, file_append_path(sdk_inc_root, "ucrt"));
    vec_add(clang_args, "-isystem");
    vec_add(clang_args, file_append_path(sdk_inc_root, "um"));
    vec_add(clang_args, "-isystem");
    vec_add(clang_args, file_append_path(sdk_inc_root, "shared"));
    vec_add(clang_args, "-isystem");
    vec_add(clang_args, file_append_path(sdk_inc_root, "winrt"));

    if (is_cpp) {
        vec_add(clang_args, "-isystem");
        vec_add(clang_args, file_append_path(sdk_inc_root, "cppwinrt"));
    }

    bool compile_only = false;
    for (int i = 0; i < argc; i++) {
        if (!argv[i]) continue;

        vec_add(clang_args, argv[i]);

        if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "/c") ||
            !strcmp(argv[i], "-E") || !strcmp(argv[i], "/P") ||
            !strcmp(argv[i], "-S") || !strcmp(argv[i], "/FA"))
            compile_only = true;
    }

    if (!compile_only) {
        vec_add(clang_args, "-Xlinker");
        vec_add(clang_args, str_cat("/libpath:", sdk_root));
        vec_add(clang_args, "-Xlinker");
        vec_add(clang_args, str_cat("/libpath:", file_append_path(sdk_root, "uwp")));
        vec_add(clang_args, "-Xlinker");
        vec_add(clang_args, str_cat("/libpath:", file_append_path(sdk_root, "store")));
        vec_add(clang_args, "-Xlinker");
        vec_add(clang_args, str_cat("/libpath:", file_append_path(sdk_root, "enclave")));
    }

    vec_add(clang_args, NULL);

    execvp(is_cpp ? "clang++" : "clang", clang_args);

    return 0;
}
