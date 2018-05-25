#pragma once

#include <iostream>
#include <mosquittopp.h>

const int QOS1 = 1;

class ConnectionManager : public mosqpp::mosquittopp {
public:
    ConnectionManager(const ConnectionManager &) = delete;
    ConnectionManager &operator =(const ConnectionManager &) = delete;
    ConnectionManager(ConnectionManager &&) = delete;
    ConnectionManager &operator =(ConnectionManager &&) = delete;

    static ConnectionManager &instance(const std::string &host, int port) {
        static ConnectionManager inst(host, port);
        return inst;
    }
    ~ConnectionManager();

    bool send_message(const std::string &topic, const std::string &message);
    bool connected() const { return connected_; }

private:
    bool connected_{};

    ConnectionManager(const std::string &host, int port);
    void async_connect(const char *host, int port, int keepalive = 60);
    void on_connect(int rc);
    void on_publish(int mid);
};
