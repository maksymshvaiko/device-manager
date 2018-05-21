#include <iostream>
#include "connectionmanager.h"

const std::string kHost = "localhost";
const int kPort = 1883;


int main() {
    std::cout << "Hello initial commit!\n";
    ConnectionManager a("127.0.0.1", 1883);
    a.send_message("esp1", "ON");
	return 0;
}
