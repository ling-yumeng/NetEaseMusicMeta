#include <iostream>
#include <fstream>
#include "lrc.h"
#include "info.h"
#include <stdlib.h>

#define debug false

int main() {
	char deb_buffer[12];

	/*
	if (debug) std::cout << "###\nPre Constructing\n###\nBreak Point (Press Enter)\n###" << std::endl;
	if (debug) std::cin.getline(deb_buffer, 12);
	lrc::lrc test("./test.lrc", 2014232695);
	if (debug) std::cout << "###\nPost Constructing\n###\nBreak Point (Press Enter)\n###" << std::endl;
	if (debug) std::cin.getline(deb_buffer, 12);

	test.write();
	if (debug) std::cout << "###\nPost Writing\n###\nBreak Point (Press Enter)\n###" << std::endl;
	if (debug) std::cin.getline(deb_buffer, 12);
	*/

	info::info sngInfo;
	char buffer[32];
	unsigned char mode;
	int id_buffer;
	std::cin.getline(buffer, 32);
	if(std::string(buffer).substr(0, std::string("get-by-name").length()) == std::string("get-by-name"))
		mode = 1;
	else if(std::string(buffer).substr(0, std::string("get-by-id").length()) == std::string("get-by-id"))
		mode = 0;
	if(mode == 1) {
		std::cin.getline(buffer, 32);
		sngInfo.get(info::info::searchByKeywords(buffer));
	}
	else {
		std::cin.getline(buffer, 32);
		sscanf(buffer, "%d", &id_buffer);
		sngInfo.get(id_buffer);
	}
	/*std::cout << "full name=" << sngInfo.name << std::endl
	<< "id=" << sngInfo.id << std::endl
	<< "artists=[" << sngInfo.artists_length << "]" << std::endl;
	for(int i = 0; i<sngInfo.artists_length; i++)
		std::cout << sngInfo.artists[i] << std::endl;
	std::cout << "album name=" << sngInfo.album_name << std::endl;
	std::cout << "cover=" << sngInfo.coverURL << std::endl;*/
	std::cin.getline(buffer, 32);
	if(std::string(buffer).substr(0, std::string("name").length()) == std::string("name")) {
		std::cout << sngInfo.name << std::endl;
	}
	else if(std::string(buffer).substr(0, std::string("id").length()) == std::string("id")) {
		std::cout.write((char*)&sngInfo.id, sizeof(sngInfo.id));
		std::cout << std::endl;
	}
	else if(std::string(buffer).substr(0, std::string("artists").length()) == std::string("artists")) {
		std::cout.write((char*)&sngInfo.artists_length, sizeof(sngInfo.artists_length));
		for(int i = 0; i<sngInfo.artists_length; i++) {
			int name_length = sngInfo.artists[i].length();
			std::cout.write((char*)&name_length, sizeof(int));
			std::cout.write(sngInfo.artists[i].c_str(), name_length);
		}
		std::cout << std::endl;
	}
	else if(std::string(buffer).substr(0, std::string("album-name").length()) == std::string("album-name")) {
		std::cout << sngInfo.album_name << std::endl;
	}
	else if(std::string(buffer).substr(0, std::string("album-id").length()) == std::string("album-id")) {
		std::cout << sngInfo.album_id << std::endl;
	}
	else if(std::string(buffer).substr(0, std::string("cover").length()) == std::string("cover")) {
		std::cout << sngInfo.coverURL << std::endl;
	}

	return 0;
}
