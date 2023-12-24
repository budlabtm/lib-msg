### budlab/lib
# Messaging

Library helps communicate with message broker in standard way. Design inspired by Apache Kafka - for more information, see: https://kafka.apache.org/36/javadoc/index.html?org/apache/kafka/

## Core
The core of the library represented by several interfaces, allowing us to use messaging system in the same ways.

### Record
`Record` is a base structure, which represent every unit located in message broker. It can be serialized/deserialized to/from string in default way (preferred) or using custom parsers.

#### Default record representation
Preferred way to represent all records in message broker is - `topic|[key|]message[|time]`, where tokens in `[]` are optional.

#### Time
Field `time` in the submitted record indicates the time the record was created.

### Client
The `Client` API allows applications to configure, connect, send and consume messages from message broker. There is only two things you must to do once using `Client` API directy - configure and connect. Sending and consuming should be implemented using `Producer` and `Consumer` APIs respectively.

### Producer
The `Producer` API allows applications to send records to message broker using corresponding `Client`.

### Consumer
The `Consumer` API allows applications to consume records from message broker in preconfigured way using corresponding `Client`.