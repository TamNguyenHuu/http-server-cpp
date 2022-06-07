#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <string>

class HttpServer
{
private:
    int m_port;
    std::string m_dir_path;

    int m_socket_fd = -1;

public:
    HttpServer(int port, std::string dir_path);
    ~HttpServer();

    void init_socket();
    void start();
};

#endif //HTTP_SERVER_H
