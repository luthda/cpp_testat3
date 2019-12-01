#include "indexableSet.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <string>
#include <stdexcept>

void testIndexAccess() {
	indexableSet<int, std::less<int>> indexSet{1, 2, 3};
	auto indexVal = indexSet[0];
	ASSERT_EQUAL(1, indexVal);
}

void testNegativeIndexAccess() {
	indexableSet<int> indexSet{1, 3, 5};
	auto indexVal = indexSet[-1];
	ASSERT_EQUAL(5, indexVal);
}

void testOutOfBoundException() {
	indexableSet<std::string> strSet{":D", ";D", "xD"};
	ASSERT_THROWS(strSet[3], std::out_of_range);
}

void thisIsATest() {
	ASSERTM("start writing tests", true);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(thisIsATest));
	s.push_back(CUTE(testIndexAccess));
	s.push_back(CUTE(testOutOfBoundException));
	s.push_back(CUTE(testNegativeIndexAccess));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
