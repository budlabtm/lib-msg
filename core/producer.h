#ifndef LIB_MSG_PRODUCER_H
#define LIB_MSG_PRODUCER_H

#include <memory>
#include <string>

#include "client.h"
#include "core/record.h"
#include "record.h"

namespace budlab::lib::msg {

class IProducer {
protected:
  std::shared_ptr<IClient> client_;
  std::string (*parser_)(Record) = nullptr;

public:
  virtual ~IProducer() {}

  virtual bool Send(const Record &record) = 0;

  void SetParser(std::string (*parser)(Record)) { parser_ = parser; }
};

} // namespace budlab::lib::msg

#endif // LIB_MSG_PRODUCER_H