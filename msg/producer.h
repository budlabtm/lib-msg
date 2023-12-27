#ifndef LIB_MSG_PRODUCER_H
#define LIB_MSG_PRODUCER_H

#include <memory>
#include <string>

#include "msg/client.h"
#include "msg/record.h"

namespace budlab::msg {

class Producer {
 private:
  std::shared_ptr<IClient> client_;

 public:
  Producer(IClient *client);
  virtual ~Producer() {}

  bool Send(const Record &record);
};

}  // namespace budlab::msg

#endif  // LIB_MSG_PRODUCER_H