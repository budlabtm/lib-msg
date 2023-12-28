load("@rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
    name = "message-handler",
    srcs = ["message-handler.cc"],
    hdrs = ["message-handler.h"],
    deps = ["//msg"],
)

cc_test(
    name = "vcas-parser-test",
    srcs = ["vcas-parser-test.cc"],
    deps = [
        "//msg",
        "//msg/vcas",
        "@gtest",
    ],
)

cc_test(
    name = "default-parser-test",
    srcs = ["default-parser-test.cc"],
    deps = [
        "//msg",
        "@gtest",
    ],
)

cc_test(
    name = "mqtt-consumer-test-manual",
    srcs = ["mqtt-consumer-test-manual.cc"],
    deps = [
        ":message-handler",
        "//msg/mqtt",
    ],
)

cc_test(
    name = "vcas-consumer-test-manual",
    srcs = ["vcas-consumer-test-manual.cc"],
    deps = [
        ":message-handler",
        "//msg/vcas",
    ],
)
