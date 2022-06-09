#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <unordered_map>
#include <sys/epoll.h>
#include <netinet/in.h>

#define PORT 8080
#define DIR_PATH "web_data" // the folder that contains the website's data

#define BACKLOG_SOCKET 5      // number of connections
#define BACKLOG_EPOLL 10      // number of epoll events
#define BUFFER_SIZE 2048      // size of buffer for reading request data
#define NUMBER_OF_THREADS 100 // number of threads

const std::string LINE_ENDING = "\r\n";
const std::string HTTP_VERSION = "HTTP/1.1";
const std::string NOT_FOUND_ERROR_MESSAGE = "The given document couldn't be found";

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
typedef struct epoll_event epoll_event;

enum class RequestMethod
{
    GET,
    POST,
    OPTIONS,
    HEAD,
    PUT,
    DELETE,
    PATCH,
};

const std::unordered_map<std::string, RequestMethod> request_method_map =
{
    {"OPTIONS", RequestMethod::OPTIONS },
    {"GET",     RequestMethod::GET     },
    {"HEAD",    RequestMethod::HEAD    },
    {"POST",    RequestMethod::POST    },
    {"PUT",     RequestMethod::PUT     },
    {"DELETE",  RequestMethod::DELETE  },
    {"PATCH",   RequestMethod::PATCH   },
};

enum RequestStatusCode
{
    OK                      = 200,
    CREATED                 = 201,
    BAD_REQUEST             = 400,
    NOT_FOUND               = 404,
    INTERNAL_SERVER_ERROR   = 500,
};

const std::unordered_map<int, std::string> request_status_code_map =
{
    {OK,                    "OK"},
    {CREATED,               "Created"},
    {BAD_REQUEST,           "Bad Request"},
    {NOT_FOUND,             "Not Found"},
    {INTERNAL_SERVER_ERROR, "Internal Server Error"},
};

#endif //CONSTANTS_H
