#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <omp.h>

namespace metadata {
    struct metadata {
        std::string title;
        std::string artist;
        std::string album;
    };
    bool setMetadata(const char* filePath, metadata info) {
        char* cmd = new char[2048]; //Using Heap memory, instead of static stack memory.
        char* fileExt = (char*)filePath;
        while (std::string(fileExt).find('.') != std::string::npos)
            fileExt += std::string(fileExt).find('.') + 1;
        sprintf(cmd, "ffmpeg -i \"%s\" -metadata title=\"%s\" -metadata artist=\"%s\" -metadata album=\"%s\" -c:a copy \"%s.tmp.%s\"", filePath, info.title, info.artist, info.album, filePath, fileExt);
        int ffmpeg_retv = system(cmd);
        if(ffmpeg_retv != 0) {
            std::cout << "FFmpeg Return with a non-zero value" << std::endl;
            delete[] cmd;
            return false;
        }
        unlink(filePath);
        sprintf(cmd, "mv \"%s.tmp.%s\" \"%s\"", filePath, fileExt, filePath);
        int mv_retv = system(cmd);
        if(mv_retv != 0) {
            std::cout << "Fail to remove" << std::endl;
            delete[] cmd;
            return false;
        }
        delete[] cmd;
        return true;
    }
    metadata getMetaData(const char* filePath) {
        char* cmd = new char[2048];
        sprintf(cmd, "ffmpeg -i '%s' -f ffmetadata '/tmp/%s.meta.txt'", filePath, filePath);
        system(cmd);
        metadata m;
        sprintf(cmd, "/tmp/%s.meta.txt", filePath);
        std::ifstream fmetadata(cmd);
        fmetadata.seekg(0, std::ios::end);
        int length = fmetadata.tellg();
        fmetadata.seekg(0, std::ios::beg);
        fmetadata.read(cmd, length);
        
        //parallel cache
        std::string m_cache_title;
        std::string m_cache_artist;
        std::string m_cache_album;
#pragma omp parallel for schedule(dynamic)
        for(int i = 0; i < 3; i++) {
            switch (i) {
                case 0: {
                    char* title = cmd;
                    title += std::string(title).find("title=") + 6;
                    m_cache_title = std::string(title).substr(0, std::string(title).find('\n'));
                    break;
                }
                case 1: {
                    char* artist = cmd;
                    artist += std::string(artist).find("artist=") + 7;
                    m_cache_artist = std::string(artist).substr(0, std::string(artist).find('\n'));
                    break;
                }
                case 2: {
                    char* album = cmd;
                    album += std::string(album).find("album=") + 7;
                    m_cache_album = std::string(album).substr(0, std::string(album).find('\n'));
                    break;
                }
            }
        }
        //Write back
        m.title = m_cache_title;
        m.artist = m_cache_artist;
        m.album = m_cache_album;

        sprintf(cmd, "/tmp/%s.meta.txt", filePath);
        unlink(cmd);
        delete[] cmd;
        return m;
    }
}

