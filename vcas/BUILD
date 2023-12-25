load("@rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
    name = "vcas",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = [
        "//core",
        "@rules_qt//:qt_network",
    ],
)
