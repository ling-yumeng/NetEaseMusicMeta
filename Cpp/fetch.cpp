#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdexcept>
#include <omp.h>

namespace fetch {
    class musicFile {
        char* filePath;
        int filePath_length;
        int id;
        const char* musicURL;
        void getURL();
    public:
        musicFile(const char* path, int id);
        void write();
    };
}