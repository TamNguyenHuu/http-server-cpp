cmake_minimum_required(VERSION 3.16)
project(http_server_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -pthread)

set(
    HEADERS include/constants.h include/epoll_wrapper.h include/exception.h include/http_server.h include/thread_pool.h include/thread_worker.h include/request/http_request_get.h include/request/http_request_post.h include/request/http_request.h
)

set(
    SOURCES src/main.cpp src/EPollWrapper.cpp src/http_server.cpp src/thread_pool.cpp src/thread_worker.cpp src/request/http_request_get.cpp src/request/http_request_post.cpp src/request/http_request.cpp
)

add_executable(http_server.out ${HEADERS} ${SOURCES})
target_link_libraries(http_server.out)
