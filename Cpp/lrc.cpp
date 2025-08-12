#include <iostream>
#include <array>
#include <omp.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <memory>
#include <stdexcept>

#define debug false

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

namespace lrc {
	lrc::lrc(const char* filePath, int id) {
		this->filePath_length = std::string(filePath).length();
		this->filePath = new char[filePath_length+1];
		#pragma omp parallel for
		for(int i = 0; i < filePath_length; i++) {
			this->filePath[i] = filePath[i];
		}
		this->filePath[filePath_length] = 0;
		this->LRC = "";
		this->id = id;
	}
	
	lrc::~lrc() {
		delete[] this->filePath;
		this->filePath_length = 0;
		this->filePath = NULL;
	}
	
	void lrc::loadLRC() {
		char cmd[64];
		sprintf(cmd, "env SID=%d bun run lrc/ptLrc.ts", this->id);
		if (debug) std::cout << "###\nBreak Here\n###\n[POST] sprintf(cmd, \"env SID=%d bun run lrc/ptLrc.ts\", this->id);" << std::endl;
		if (debug) std::cout << "cmd: " << cmd << std::endl;
		char deb_buffer[12];
		if (debug) std::cin.getline(deb_buffer, 12);
		std::array<char, 64> rbuffer;
		std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd,"r"), pclose);
		if (debug) std::cout << "###\nBreak Here\n###\n[POST] std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd,\"r\"), pclose);" << std::endl;
		if (debug) std::cin.getline(deb_buffer, 12);
		if (!pipe) {
			std::cout << "###\npopen() failed!\n###" << std::endl;
			std::cin.getline(deb_buffer, 12);
			throw std::runtime_error("popen() failed!");
		}
		if (debug) std::cout << "###\nBreak Here\n###\n About to get data from pipe" << std::endl;
		if (debug) std::cin.getline(deb_buffer, 12);
		while (fgets(rbuffer.data(), rbuffer.size(), pipe.get()) != nullptr) {
			this->LRC += rbuffer.data();
		}
		if (debug) std::cout << "###\nBreak Here\n###\n Data Fetch Done!" << std::endl;
		if (debug) std::cin.getline(deb_buffer, 12);
	}
	
	void lrc::write() {
		this->loadLRC();
		std::ofstream lrcFile(this->filePath);
		lrcFile.write(this->LRC.c_str(), this->LRC.length());
		lrcFile.close();
	}
}
