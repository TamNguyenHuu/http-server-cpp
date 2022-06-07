#include <iostream>
#include <string>
#include <cstring>
#include <signal.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../include/constants.h"
#include "../include/http_server.h"
#include "../include/request/http_request.h"

HttpServer::HttpServer(int port, std::string dir_path) : m_port(port), m_dir_path(dir_path)
{
    init_socket();
}

HttpServer::~HttpServer()
{
    if (m_server_fd != -1)
    {
        shutdown(m_server_fd, SHUT_RDWR);
        std::cout << "Http server is closed" << std::endl;
    }
}

void HttpServer::init_socket()
{
    sockaddr_in addr;
    int reuse = 1;

    if ((m_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cout << "socket: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
    {
        std::cout << "setsockopt: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_server_fd, (sockaddr*) &addr, sizeof(sockaddr)) == -1)
    {
        std::cout << "bind: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(m_server_fd, BACKLOG_SOCKET) == -1)
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
    m_epoll = new EPollWrapper(m_server_fd);
    m_epoll->start_waitting
    (
        [&](){ return accept_new_connection(); },
        [&](int client_fd){ return handle_client_request(client_fd); }
    );
}

int HttpServer::accept_new_connection()
{
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd;

    if ((client_fd = accept(m_server_fd, (struct sockaddr *) &client_addr, &client_addr_len)) == -1)
    {
        std::cout << "accept: " << std::strerror(errno) << std::endl;
    }
    std::cout << "Connection to " << inet_ntoa(client_addr.sin_addr) << " established (fd = " << client_fd << ")" << std::endl;

    return client_fd;
}


void HttpServer::handle_client_request(int client_fd)
{
    char buffer[BUFFER_SIZE] = {0};

    if (read(client_fd, buffer, BUFFER_SIZE) == 0)
    {
        std::cout << "Connection lost, fd = " << client_fd << std::endl;
        m_epoll->del_client_fd(client_fd);
        close(client_fd);
        return;
    }

    HttpRequest* request = HttpRequest::CreateNewHttpRequest(buffer, m_dir_path);
    std::string response = request->GetResponse();

    write(client_fd, response.c_str(), response.size());
}
