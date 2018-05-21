#include <iostream>
#include "connectionmanager.h"

//TODO: Read from configuration file
const std::string kHost = "localhost";
const int kPort = 1883;


int main() {
    std::cout << "Hello initial commit!\n";
    ConnectionManager client(kHost, kPort);

    client.send_message("esp1", "ON");
	return 0;
}
