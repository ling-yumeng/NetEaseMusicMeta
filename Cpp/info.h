#pragma once
#include <string>

namespace info {
	class info {
	public:
		int id;
		std::string name;
		std::string* artists;
		int artists_length;
		int album_id;
		std::string album_name;
		std::string coverURL;
		bool init;
		info();
		~info();
		static int searchByKeywords(const char* keywords);
		void get(int id);
		void getInfoByKeywords(const char* keywords);
	};
}
