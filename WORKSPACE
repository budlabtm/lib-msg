load("//:lib_msg_deps.bzl", "lib_msg_deps")

lib_msg_deps()

load("@rules_qt//:fetch_qt.bzl", "fetch_qt6")

fetch_qt6()

load("@rules_qt//tools:qt_toolchain.bzl", "register_qt_toolchains")

register_qt_toolchains()

load("@paho-mqtt-cpp//:paho_mqtt_cpp_deps.bzl", "paho_mqtt_cpp_deps")

paho_mqtt_cpp_deps()

load("@paho-mqtt-c//:paho_mqtt_c_deps.bzl", "paho_mqtt_c_deps")

paho_mqtt_c_deps()
