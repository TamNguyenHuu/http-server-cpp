#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>

class HttpSocketException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class EpollException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class HttpParserException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

#endif //EXCEPTIONS_H
