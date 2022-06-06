#include <iostream>
#include <filesystem>

#include "../include/constants.h"

int main(int argc, char **argv) {
    if (!std::filesystem::is_directory(std::filesystem::path(DIR))) {
        std::cerr << "Invalid directory\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
