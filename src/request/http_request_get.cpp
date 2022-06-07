#include <iostream>
#include <fstream>
#include <filesystem>
#include "../../include/request/http_request_get.h"
#include "../../include/constants.h"

HttpRequestGet::HttpRequestGet(const std::string& content, const std::string& dir_path) : HttpRequest(content, dir_path)
{
    std::cout << "Create HttpRequestGet" << std::endl;
}

std::string HttpRequestGet::GetResponse()
{
    std::string response;
    std::string file_path = std::string(m_dir_path + "/" + m_url);

    std::ifstream ifs(file_path);
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    if (ifs.good())
    {
        auto status_code_pair = request_status_code_map.find(OK);

        // response line
        response.append(HTTP_VERSION);
        response.append(" ");
        response.append(std::to_string(status_code_pair->first));
        response.append(" ");
        response.append(status_code_pair->second);
        response.append(LINE_ENDING);

        // content
        response.append("Content-Length: ");
        response.append(std::to_string(content.size()));
        response.append(LINE_ENDING);
        response.append(LINE_ENDING);
        response.append(content);
    }
    else if (!std::filesystem::exists(file_path))
    {
        // 404 error
        response.append(HTTP_VERSION);
        response.append(" 404 Not Found");
        response.append(LINE_ENDING);
        response.append("Content-Length: ");
        response.append(std::to_string(NOT_FOUND_ERROR_MESSAGE.size()));
        response.append(LINE_ENDING);
        response.append(LINE_ENDING);
        response.append(NOT_FOUND_ERROR_MESSAGE);
    }

    return response;
}

