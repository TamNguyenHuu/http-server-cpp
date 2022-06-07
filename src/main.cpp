#include <iostream>
#include <filesystem>

#include "../include/constants.h"
#include "../include/http_server.h"

int main(int argc, char **argv) {
    if (!std::filesystem::is_directory(std::filesystem::path(DIR_PATH))) {
        std::cerr << "Invalid directory\n";
        return EXIT_FAILURE;
    }

    HttpServer server(PORT, DIR_PATH);
    server.start();

    return EXIT_SUCCESS;
}
