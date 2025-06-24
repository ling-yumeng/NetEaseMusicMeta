#pragma once
#include <string>

namespace lrc {
	class lrc {
		char* filePath;
		int filePath_length;
		std::string LRC;
		int id;
		void loadLRC();
	public:
		lrc(const char* filePath, int id);
		~lrc();
		void write();
	};
}
