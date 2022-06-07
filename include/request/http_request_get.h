#ifndef HTTP_REQUEST_GET_H
#define HTTP_REQUEST_GET_H

#include "http_request.h"

class HttpRequestGet : public HttpRequest
{
public:
    HttpRequestGet(const std::string& content, const std::string& dir_path);
    virtual std::string GetResponse();
};

#endif //HTTP_REQUEST_GET_H
