#include <iostream>
#include <string>
#include <cstring>
#include <signal.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../include/constants.h"
#include "../include/http_server.h"
#include "../include/request/http_request.h"

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

HttpServer::HttpServer(int port, std::string dir_path) : m_port(port), m_dir_path(dir_path)
{
    init_socket();
}

HttpServer::~HttpServer()
{
    if (m_socket_fd != -1)
    {
        shutdown(m_socket_fd, SHUT_RDWR);
        std::cout << "Http server is closed" << std::endl;
    }
}

void HttpServer::init_socket()
{
    sockaddr_in addr;
    int reuse = 1;

    if ((m_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cout << "socket: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(m_socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
    {
        std::cout << "setsockopt: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_socket_fd, (sockaddr*) &addr, sizeof(sockaddr)) == -1)
    {
        std::cout << "bind: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(m_socket_fd, BACKLOG_SOCKET) == -1)
    {
        std::cout << "listen: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Http server is listening on port: " << m_port << std::endl;
    }
}

void HttpServer::start()
{
    char buffer[BUFFER_SIZE] = {0};
    sockaddr_in client_addr;
    int addrlen = sizeof(client_addr);

    int client_fd = -1;
    if ((client_fd = accept(m_socket_fd, (sockaddr*)&client_addr, (socklen_t*)&addrlen)) < 0)
    {
        std::cout << "accept: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    if (read(client_fd, buffer, BUFFER_SIZE) == 0)
    {
        std::cout << "Connection lost, fd = " << client_fd << std::endl;
        close(client_fd);
        return;
    }

    std::cout << "Request content = " << buffer << std::endl;

    HttpRequest* request = HttpRequest::CreateNewHttpRequest(buffer, m_dir_path);
    std::string response = request->GetResponse();

    write(client_fd, response.c_str(), response.size());
}
