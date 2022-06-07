#ifndef HTTP_REQUEST_POST_H
#define HTTP_REQUEST_POST_H

#include "http_request.h"

class HttpRequestPost : public HttpRequest
{
public:
    HttpRequestPost(const std::string& content, const std::string& dir_path);
    virtual std::string GetResponse();
};

#endif //HTTP_REQUEST_POST_H
