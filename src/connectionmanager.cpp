#include "connectionmanager.h"

ConnectionManager::ConnectionManager(const std::string &host, int port) {
    mosqpp::lib_init();
    async_connect(host.c_str(), port);
}

ConnectionManager::~ConnectionManager() {
    loop_stop();
    mosqpp::lib_cleanup();
}

bool ConnectionManager::send_message(const std::string &topic, const std::string &message) {
    int ret = publish(NULL ,topic.c_str(), message.length(), message.c_str(), QOS1, false);
    return ( ret == MOSQ_ERR_SUCCESS );
}

void ConnectionManager::async_connect(const char *host, int port, int keepalive /* = 60*/) {
    mosqpp::mosquittopp::connect(host, port, keepalive);
    loop_start();
}

void ConnectionManager::on_connect(int rc) {
    if (!rc) {
        //TODO: LOG Output
        std::cout << "ConnectionManager - connected with server" << std::endl;
        connected_ = true;
    } else {
        std::cout << "ConnectionManager - Impossible to connect with server("
                  << rc << ")" << std::endl;
    }
}

void ConnectionManager::on_publish(int mid) {
    std::cout << "ConnectionManager - Message ("
              << mid << ") succeed to be published " << std::endl;
}
