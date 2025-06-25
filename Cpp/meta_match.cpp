#include "metadata.h"
#include "info.h"
#include "lrc.h"
#include <fstream>

namespace meta_match {
    bool match(const char* filePath, int id) {
        info::info music;
        music.get(id);
        metadata::metadata remoteMetadata;
        remoteMetadata.title = music.name;
        for(int i=0; i < music.artists_length; i++) {
            remoteMetadata.artist += music.artists[i];
            if(i < (music.artists_length - 1))
                remoteMetadata.artist += ";";
        }
        remoteMetadata.album = music.album_name;

        metadata::metadata localMetadata = metadata::getMetaData(filePath);
        
        bool correct = true;
        bool meta_correct = true;
        if(localMetadata.title != remoteMetadata.title)
            meta_correct = false;
        if(localMetadata.artist != remoteMetadata.artist)
            meta_correct = false;
        if(localMetadata.album != remoteMetadata.album)
            meta_correct = false;

        if(!meta_correct) {
            correct = false;
            metadata::setMetadata(filePath, remoteMetadata);
        }

        char* lrcPath = new char[std::string(filePath).length() + 16];
        sprintf(lrcPath, filePath);
        char* fileExt = lrcPath;
        while(std::string(fileExt).find('.') != std::string::npos)
            fileExt += std::string(fileExt).find('.') + 1;
        sprintf(fileExt, "lrc");
        
        lrc::lrc rlrcFile(lrcPath, id);
        rlrcFile.write();
        return correct;
    }
}