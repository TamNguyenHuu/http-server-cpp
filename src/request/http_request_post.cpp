#include <iostream>
#include "../../include/request/http_request_post.h"

HttpRequestPost::HttpRequestPost(const std::string& content, const std::string& dir_path) : HttpRequest(content, dir_path)
{
    std::cout << "Create HttpRequestPost" << std::endl;
}

std::string HttpRequestPost::GetResponse()
{
    // TBD
    return std::string();
}

