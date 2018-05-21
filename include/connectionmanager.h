#pragma once

#include <mosquittopp.h>

const int QOS1 = 1;

class ConnectionManager : public mosqpp::mosquittopp {
public:
    ConnectionManager(const std::string &host, int port);
    ~ConnectionManager();

    bool send_message(const std::string &topic, const std::string &message);
    bool connected() const { return connected_; }

private:
    bool connected_{};

    void async_connect(const char *host, int port, int keepalive = 60);
    void on_connect(int rc);
    void on_publish(int mid);
};
