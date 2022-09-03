#include <string>

class message {
public:
    std::string version = VERSION;
    std::string config = BUILD_INFO;
    message();
    message(std::string message);
    message(std::string message, unsigned int priority);
private:
    std::string data = "";
    unsigned int priority = 0;
};