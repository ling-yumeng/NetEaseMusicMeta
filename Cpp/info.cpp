#include <iostream>
#include <array>
#include <omp.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <memory>
#include <stdexcept>

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

namespace info {
	info::info() {
		this->id = 0;
		this->name = "";
		this->artists = NULL;
		this->artists_length = 0;
		this->album_id = 0;
		this->album_name = "";
		this->coverURL = "";
		this->init = false;
	}
	info::~info() {
		this->id = 0;
		this->name = "";
		delete[] this->artists;
		this->artists_length = 0;
		this->album_id = 0;
		this->album_name = "";
		this->coverURL = "";
		this->init = false;
	}
	int info::searchByKeywords(const char* keywords) {
		char cmd[64];
		sprintf(cmd, "env KEYWORDS=\"%s\" bun run info/search.ts", keywords);
		char rbuffer[64];
		std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd,"r"), pclose);
		if(!pipe) {
			throw std::runtime_error("popen failed!");
		}
		std::string output = "";
		while (fgets(rbuffer, 32, pipe.get()) != nullptr) {
			output += rbuffer;
		}
		int id=0;
		sscanf(output.c_str(), "%d", &id);
		return id;
	}
	void info::get(int id) {
		auto readInfo = [](int id, const char* type) {
			char cmd[128];
			sprintf(cmd, "env SID=%d TYPE=%s bun run info/getDetail.ts", id, type);
			char rbuffer[64];
			std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd,"r"), pclose);
			if(!pipe) {
				throw std::runtime_error("popen failed!");
			}
			std::string output = "";
			while (fgets(rbuffer, 32, pipe.get()) != nullptr) {
				output += rbuffer;
			}
			return output;
		};
#pragma omp parallel for
		for(int i = 0; i<6; i++) {
			switch (i) {
				case 0: {
					this->id = id;
					break;
				}
				case 1: {
					this->name = readInfo(id, "fullname");
					break;
				}
				case 2: {
					auto buffer_2 = readInfo(id, "artists");
					int artists_num;
					sscanf(buffer_2.c_str(), "%d", &artists_num);
					this->artists = new std::string[artists_num];
					this->artists_length = artists_num;
					int* artist_name_length = new int[artists_num];
					const char* buffer_c = buffer_2.c_str();
					buffer_c += buffer_2.find(' ');
					buffer_c ++;
					for(int j = 0; j < artists_num; j++) {
						sscanf(buffer_c, "%d ", artist_name_length + j);
						buffer_c += std::string(buffer_c).find(' ') + 1;
					}
					for(int j = 0; j < artists_num; j++) {
						this->artists[j] = std::string(buffer_c).substr(0, artist_name_length[j]);
						buffer_c += artist_name_length[j];
					}
					delete[] artist_name_length;
					artist_name_length = NULL;
					buffer_c = NULL;
					break;
				}
				case 3: {
					auto buffer_3 = readInfo(id, "album_id");
					sscanf(buffer_3.c_str(), "%d", &this->album_id);
					break;
				}
				case 4: {
					this->album_name = readInfo(id, "album_name");
					break;
				}
				case 5: {
					this->coverURL = readInfo(id, "cover");
					break;
				}
			}
		}
		this->init = true;
	}
	void info::getInfoByKeywords(const char* keywords) {
		int id = info::searchByKeywords(keywords);
		this->get(id);
	}
}
