load("@rules_proto_grpc_cpp//:defs.bzl", "cpp_grpc_library")
# load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
proto_library(
  name="uuid_proto",
  srcs=["uuid.proto"],
)

cc_proto_library(
    name = "uuid_cc_proto",
    deps = [":uuid_proto"],
)

cpp_grpc_library(
    name = "uuid_cpp_grpc",
    protos = [":uuid_proto"],
)

cc_binary(
  name="distributor",
  srcs=["distributor.cc"],
  deps=["@jsoncpp//:jsoncpp", "@glog//:glog", ":uuid_cc_proto", "@grpc//:grpc++", ":uuid_cpp_grpc"]
)

cc_binary(
  name="generator",
  srcs=["generator.cc"],
  deps=["@glog//:glog", ":uuid_cc_proto", ":uuid_cpp_grpc"]
)
