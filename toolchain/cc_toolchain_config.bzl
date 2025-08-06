'''Contains all the dependencies'''
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",    # NEW
    "flag_group", # NEW
    "flag_set",   # NEW
    "tool_path",
    "action_config",
    "tool",
)

all_link_actions = [ # NEW
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

all_compile_actions = [
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.c_compile,
]

def _impl(ctx):
    """Implementation of the cc_toolchain_config rule."""
    root_path = "/usr/bin/"
    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        toolchain_identifier = "macos_aarch64-toolchain",
        host_system_name = "local",
        target_system_name = "macos",
        target_cpu = "arm64",
        target_libc = "macosx",
        compiler = "clang",
         cxx_builtin_include_directories = [
            "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include",
            "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/16/include",
            "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/CoreFoundation.framework/Headers",
        ],
        tool_paths = [
            tool_path(name = "gcc", path = root_path +"g++"),
            tool_path(name = "ld", path = "/usr/bin/ld"),
            tool_path(name = "ar", path = "/usr/bin/libtool"),
            tool_path(name = "cpp", path = root_path +"g++"),
            tool_path(name = "gcov", path = "/usr/bin/gcov"),
            tool_path(name = "nm", path = "/usr/bin/nm"),
            tool_path(name = "objdump", path = "/usr/bin/objdump"),
            tool_path(name = "strip", path = "/usr/bin/strip"),
        ],
        features = [
            feature(
                name = "cxx_std_23",
                enabled = True,
                flag_sets = [
                    flag_set(
                        actions = all_link_actions,
                        flag_groups = [
                            flag_group(
                                flags = ["-std=c++23"],
                            ),
                        ],
                    ),
                ],
            ),
            feature(
                name = "c99_feature",
                enabled = True,
                flag_sets = [
                    flag_set(
                        actions = all_compile_actions,
                        flag_groups = [
                            flag_group(flags = ["-fPIC"]),
                        ],
                    ),
                ],
            ),
        ],
        action_configs = [
            action_config(
                action_name = ACTION_NAMES.c_compile,
                tools = [
                    tool(path = root_path + "clang"),
                ],
                flag_sets = [
                    flag_set(
                        flag_groups = [
                            flag_group(flags = ["-std=c99"]),
                        ],
                    ),
                ],
            ),
            action_config(
                action_name = ACTION_NAMES.cpp_compile,
                tools = [
                    tool(path = root_path + "g++"),
                ],
                flag_sets = [
                    flag_set(
                        flag_groups = [
                            flag_group(flags = ["-std=c++23"]),
                        ],
                    ),
                ],
            ),
        ]

    )

cc_toolchain_config_rule = rule(
    implementation = _impl,
    # This rule doesn't need to take any attributes, but you could add them
    # here to make it more flexible.
)
