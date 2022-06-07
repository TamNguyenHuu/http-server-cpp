#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>

class HttpRequest
{
private:
    void deserialize(const std::string& content);

protected:
    std::string m_url;
    std::string m_dir_path;

public:
    HttpRequest(const std::string& content, const std::string& dir_path);
    virtual std::string GetResponse();

    static HttpRequest* CreateNewHttpRequest(const std::string& content, const std::string& dir_path);
};

#endif //HTTP_REQUEST_H
