#pragma once
#include <string>

namespace metadata {
    struct metadata {
        std::string title;
        std::string artist;
        std::string album;
    };
    bool setMetadata(const char* filePath, metadata info);
    metadata getMetaData(const char* filePath);
}

