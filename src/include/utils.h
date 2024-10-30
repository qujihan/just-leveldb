#pragma once
#include <filesystem>
#include <string>
#include "config.h"

const std::string dir_path = LEVELDB_DATA_DIR_PATH;

inline std::string get_database_path(std::string filename, bool clean_database = false) {
    size_t pos = filename.find_last_of(".");
    std::string filenameWithoutExtension = filename.substr(0, pos);

    if (!std::filesystem::exists(dir_path)) {
        std::filesystem::create_directory(dir_path);
    } else {
        if (clean_database) {
            std::filesystem::remove_all(dir_path);
            std::filesystem::create_directory(dir_path);
        }

    }

    return dir_path + filenameWithoutExtension;
}