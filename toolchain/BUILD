load(":cc_toolchain_config.bzl", "cc_toolchain_config_rule")

package(default_visibility = ["//visibility:public"])

# Instantiate your custom toolchain config rule.
cc_toolchain_config_rule(
    name = "macos_aarch64_config",
)

cc_toolchain(
    name = "macos_aarch64_toolchain",
    toolchain_config = ":macos_aarch64_config",
    toolchain_identifier = "macos_aarch64-toolchain",
    target_compatible_with = [
        "@platforms//os:osx",
        "@platforms//cpu:arm64",
    ],
    all_files = "@bazel_tools//tools/cpp:empty",
    compiler_files = "@bazel_tools//tools/cpp:empty",
    dwp_files = "@bazel_tools//tools/cpp:empty",
    linker_files = "@bazel_tools//tools/cpp:empty",
    objcopy_files = "@bazel_tools//tools/cpp:empty",
    strip_files = "@bazel_tools//tools/cpp:empty",
)

toolchain(
    name = "cc_toolchain_macos_aarch64",
    toolchain = ":macos_aarch64_toolchain",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
    exec_compatible_with = [
        "@platforms//cpu:arm64",
        "@platforms//os:macos",
    ],
    target_compatible_with = [
        "@platforms//cpu:arm64",
        "@platforms//os:macos",
    ],
)

# Optional: You may also need a cc_toolchain_suite to register the toolchain.
cc_toolchain_suite(
    name = "toolchain_suite",
    toolchains = {
        "arm64|macosx": ":macos_aarch64_toolchain",
    },
)
