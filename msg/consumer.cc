#include "msg/consumer.h"

using namespace budlab::msg;
using namespace std;

Consumer::Consumer(IClient *client) {
  client_.reset(client);

  connect(dynamic_cast<QObject *>(client_.get()), SIGNAL(Consumed(Record)),
          this, SLOT(OnConsumed(Record)));
}

void Consumer::Subscribe(const string &topic) { Subscribe(topic, ""); }

void Consumer::Subscribe(const string &topic, const string &key) {
  if (subscribed_.count(topic) == 0) client_->Subscribe(topic);
  subscribed_.insert_or_assign(topic, key);
}

void Consumer::Unsubscribe(const string &topic) {
  if (subscribed_.count(topic) != 0) {
    subscribed_.extract(topic);
    client_->Unsubscribe(topic);
  }
}

void Consumer::OnConsumed(Record record) {
  if (subscribed_.count(record.topic) != 0 &&
      (subscribed_[record.topic].empty() ||
       subscribed_[record.topic] == record.key))
    emit Consumed(record);
}