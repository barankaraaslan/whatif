#include "important_message.h"
#include <string>

message::message() {
}
message::message(std::string data) {
    this->data = data;
}
message::message(std::string data, unsigned int priority) {
    this->data = data;
    this->priority = priority;
}