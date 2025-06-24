#include <iostream>
#include <fstream>
#include "lrc.h"
#include "info.h"

int main() {
	lrc::lrc test("./test.lrc", 2014232695);
	test.write();
	info::info sngInfo;
	sngInfo.get(2014232695);
	std::cout << sngInfo.name << std::endl
		<< sngInfo.coverURL << std::endl;
	return 0;
}
