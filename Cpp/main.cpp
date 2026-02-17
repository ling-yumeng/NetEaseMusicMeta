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
	std::cout << "full name=" << sngInfo.name << std::endl
	<< "id=" << sngInfo.id << std::endl
	<< "artists=[" << sngInfo.artists_length << "]" << std::endl;
	for(int i = 0; i<sngInfo.artists_length; i++)
		std::cout << sngInfo.artists[i] << std::endl;
	std::cout << "album name=" << sngInfo.album_name << std::endl;
	std::cout << "cover=" << sngInfo.coverURL << std::endl;

	return 0;
}
