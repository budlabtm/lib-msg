#ifndef LIB_MSG_PRODUCER_H
#define LIB_MSG_PRODUCER_H

#include <memory>
#include <string>

#include "client.h"
#include "core/record.h"
#include "record.h"

namespace budlab::lib::msg {

class Producer {
 private:
  std::shared_ptr<IClient> client_;

 public:
  Producer(IClient *client);
  virtual ~Producer() {}

  bool Send(const Record &record);
};

}  // namespace budlab::lib::msg

#endif  // LIB_MSG_PRODUCER_H