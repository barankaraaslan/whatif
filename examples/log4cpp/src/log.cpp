#include <string>
#include <iostream>
void log(std::string msg) {
    std::cout << "LOG4CPP: " << msg << std::endl;
}
void build_info() {
    std::cout << "Build Config: " << BUILD_INFO << std::endl;
    std::cout << "Build Config: " << VERSION << std::endl;
}