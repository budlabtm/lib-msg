load("@rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
    name = "mqtt",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = [
        "//msg",
        "@glog",
        "@mqtt//:paho-mqtt-cpp-linux",
    ],
)
