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
	std::cout << info::info::searchByKeywords("") << std::endl;
	return 0;
}
