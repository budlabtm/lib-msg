load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def lib_msg_deps():
    if not native.existing_rule("glog"):
        http_archive(
            name = "com_github_gflags_gflags",
            sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
            strip_prefix = "gflags-2.2.2",
            urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
        )

        http_archive(
            name = "glog",
            sha256 = "122fb6b712808ef43fbf80f75c52a21c9760683dae470154f02bddfc61135022",
            strip_prefix = "glog-0.6.0",
            urls = ["https://github.com/google/glog/archive/v0.6.0.zip"],
        )

    if not native.existing_rule("gtest"):
        http_archive(
            name = "gtest",
            urls = ["https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip"],
            strip_prefix = "googletest-f8d7d77c06936315286eb55f8de22cd23c188571",
        )

    if not native.existing_rule("paho-mqtt-cpp"):
        http_archive(
            name = "paho-mqtt-cpp",
            sha256 = "dc44c26e26fc9eca9375bdf66ae0b755fa3125f3632264e2bf17f0fa688f30ab",
            strip_prefix = "paho-mqtt-cpp-1.3.2",
            urls = ["https://github.com/mehandes/paho-mqtt-cpp/archive/refs/tags/v1.3.2.tar.gz"],
        )

    if not native.existing_rule("rules_qt"):
        http_archive(
            name = "rules_qt",
            sha256 = "bd8253247c0e45e6a180c87083f20910159e36cd67f6b11d5d3d865a61ea52cd",
            strip_prefix = "rules_qt6-0.0.3",
            url = "https://github.com/Vertexwahn/rules_qt6/releases/download/v0.0.3/rules_qt6-v0.0.3.tar.gz",
        )
