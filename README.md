### budlab/lib
# Messaging

The module serves to communicate with several brokers and transmits messages in a simple and standardized way. Design inspired by Apache Kafka client library - for more information see: https://kafka.apache.org/36/javadoc/index.html?org/apache/kafka/



## Installation

You can add a module to your Bazel project using WORKSPACE dependency system. In order to do this, add the following line in your WORKSPACE file:

``` python
http_archive(
    name = "msg",
    sha256 = "5537fbd138ae3c02d7a4ce1a6032533c4f9248699a8cb7e9640d6f15999e019d",
    strip_prefix = "lib-msg-1.0.0-linux",
    url = "https://github.com/budlabtm/lib-msg/archive/refs/tags/v1.0.0-linux.tar.gz",
)
```

You will then able to access the module using the specified repository name. For example, you can access an MQTT submodule by specifying the following dependency:

```python
deps = ["@msg//msg/mqtt"]
```

As an addition, you must to add `rules_qt` dependency before `msg` declaration:

``` python
http_archive(
    name = "rules_qt",
    sha256 = "bd8253247c0e45e6a180c87083f20910159e36cd67f6b11d5d3d865a61ea52cd",
    strip_prefix = "rules_qt6-0.0.3",
    url = "https://github.com/Vertexwahn/rules_qt6/releases/download/v0.0.3/rules_qt6-v0.0.3.tar.gz",
)
```

## Targets

Here is the complete list of available targets with a brief description:

- `@msg//msg` - Library core, including API interfaces and clients.
- `@msg//msg/vcas` - VCAS implementation.
- `@msg//msg/mqtt` - MQTT implementation.
- `@msg//test:vcas-parser-test` - Tests for default VCAS parser.
- `@msg//test:default-parser-test` - Tests for default parser (MQTT).
- `@msg//test:mqtt-consumer-test-manual` - Manual test for MQTT implementation. See {projectFolder}/msg/test/mqtt-consumer-test-manual.cc



## Usage

In order to start messaging you need to instantiate and configure `IClients` for each implementation you want to use and pass it to `Producers` and `Consumers`. For example:

``` c++
#include <QtCore/QCoreApplication>

#include <msg/mqtt/mqtt-client.h>
#include <msg/consumer.h>
#include <msg/producer.h>

using namespace budlab::msg;

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);
  IClient *client = new MqttClient();

  client->Configure(Configuration("hostname", "password"));

  Consumer consumer(client);
  Producer producer(client);

  return app.exec();
}
```

## Logging

The module uses Google Logging C++ library (see https://github.com/google/glog) as a logging system. To include it in your project, add the folloing:

``` c++
#include <glog/logging.h>
```

and the following line at the start of your `main()`:

``` c++
google::InitGoogleLogging(argv[0]);
```
