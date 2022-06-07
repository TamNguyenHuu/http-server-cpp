#include <iostream>
#include <functional>

#include "../../include/request/http_request.h"
#include "../../include/request/http_request_get.h"
#include "../../include/request/http_request_post.h"
#include "../../include/constants.h"

std::unordered_map<RequestMethod, std::function< HttpRequest*(const std::string&, const std::string&)>> request_generator_by_method =
{
    {RequestMethod::GET     , [](const std::string& content, const std::string& dir_path){ return new HttpRequestGet(content, dir_path); } },
    {RequestMethod::POST    , [](const std::string& content, const std::string& dir_path){ return new HttpRequestPost(content, dir_path); } },
    {RequestMethod::OPTIONS , [](const std::string& content, const std::string& dir_path){ return new HttpRequest(content, dir_path); } },
    {RequestMethod::HEAD    , [](const std::string& content, const std::string& dir_path){ return new HttpRequest(content, dir_path); } },
    {RequestMethod::PUT     , [](const std::string& content, const std::string& dir_path){ return new HttpRequest(content, dir_path); } },
    {RequestMethod::DELETE  , [](const std::string& content, const std::string& dir_path){ return new HttpRequest(content, dir_path); } },
    {RequestMethod::PATCH   , [](const std::string& content, const std::string& dir_path){ return new HttpRequest(content, dir_path); } },
};

HttpRequest::HttpRequest(const std::string& content, const std::string& dir_path) : m_dir_path(dir_path)
{
    deserialize(content);
}

void HttpRequest::deserialize(const std::string& content)
{
    // Get URL
    size_t end_of_method_pos = content.find_first_of(' ', 0);
    size_t end_of_url_pos = content.find_first_of(' ', end_of_method_pos + 1);
    if (end_of_url_pos == std::string::npos)
    {
        std::cout << "No URL substring found" << std::endl;
        exit(EXIT_FAILURE);
    }
    m_url = content.substr(end_of_method_pos + 1, end_of_url_pos - end_of_method_pos - 1);

    if (m_url == "/")
    {
        m_url = "index.html";
    }
}

std::string HttpRequest::GetResponse()
{
    return std::string();
}

HttpRequest* HttpRequest::CreateNewHttpRequest(const std::string& content, const std::string& dir_path)
{
    // Get String method of request
    size_t end_of_method_pos = content.find_first_of(' ', 0);
    std::string request_method_str = content.substr(0, end_of_method_pos);
    if (end_of_method_pos == std::string::npos) {
        std::cout << "No HTTP-Method substring found" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Get Enum method of request
    auto method_it = request_method_map.find(request_method_str);
    if (method_it == request_method_map.end()) {
        std::cout << "No valid HTTP-Method found" << std::endl;
        exit(EXIT_FAILURE);
    }
    RequestMethod method = method_it->second;

    // Get request generator
    std::function<HttpRequest*(const std::string&, const std::string&)> request_generator = request_generator_by_method.find(method)->second;

    // Return new HttpRequest
    return request_generator(content, dir_path);
}


