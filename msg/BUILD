load("@rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
    name = "msg",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = ["@rules_qt//:qt_core"],
)
