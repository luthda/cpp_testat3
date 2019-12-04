#include "indexableSet.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <stdexcept>
#include <string>
#include <iterator>

struct caseless {
	bool operator()(std::string const &lhs, std::string const &rhs) const {
		return std::lexicographical_compare(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs), [] (char leftChar, char rightChar) {
			return tolower(leftChar) > tolower(rightChar);
		});
	}
};

void testIndexAccess() {
	indexableSet<int, std::less<int>> indexSet{1, 2, 3};
	int indexVal = indexSet[0];
	ASSERT_EQUAL(1, indexVal);
}

void testNegativeIndexAccess() {
	indexableSet<int> indexSet{1, 3, 5};
	int indexVal = indexSet[-1];
	ASSERT_EQUAL(5, indexVal);
}

void testNegativeAtAccess() {
	indexableSet<int> indexSet{1, 3, 5, 7};
	int indexVal = indexSet.at(-1);
	ASSERT_EQUAL(7, indexVal);
}

void testNegativeIndexAccess2() {
	indexableSet<int> indexSet{1, 3, 5};
	ASSERT_EQUAL(1, indexSet.at(-3));
	ASSERT_EQUAL(1, indexSet[-3]);
}

void testOutOfBoundException() {
	indexableSet<std::string> strSet{":D", ";D", "xD"};
	ASSERT_THROWS(strSet[3], std::out_of_range);
}

void testFrontMethod() {
	indexableSet<int> indexSet{1, 2, 3};
	int indexVal = indexSet.front();
	ASSERT_EQUAL(1, indexVal);
}

void testBackMethod() {
	indexableSet<int> indexSet{1, 2, 3};
	int indexVal = indexSet.back();
	ASSERT_EQUAL(3, indexVal);
}
void testInitListCtor() {
	indexableSet<std::string> strSet{":D", ";D", "xD", ":)", ";)"};
	ASSERT_EQUAL(5, strSet.size());
}

void testEmptyMethodFromBase() {
	indexableSet<int> indexSet{ };
	ASSERT(indexSet.empty());
}

void testAccessEmptySet() {
	indexableSet<int> indexSet{ };
	ASSERT_THROWS(indexSet[0], std::out_of_range);
	ASSERT_THROWS(indexSet.front(), std::out_of_range);
}

void testCopyCtor() {
	indexableSet<std::string> strSet{":D", ";D", "xD", ":)", ";)"};
	indexableSet<std::string> copySet{strSet};
	ASSERT_EQUAL(copySet.size(), strSet.size());
}

void testGreaterComperator() {
	indexableSet<int, std::greater<int>> intSet{1, 2, 4, 6, 99};
	ASSERT_EQUAL(99, intSet.front());
	ASSERT_EQUAL(1, intSet.back());
}

void testLessComperator() {
	indexableSet<int, std::less<int>> intSet{1, 2, 4, 6, 99};
	ASSERT_EQUAL(1, intSet.front());
	ASSERT_EQUAL(99, intSet.back());
}

void testGreaterForStringFunctor() {
	indexableSet<std::string, caseless> strSet{"HI", "lol", "xD", "alf", "cpp", "no more testats!!"};
	ASSERT_EQUAL("xD", strSet.front());
	ASSERT_EQUAL("alf", strSet.back());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testIndexAccess));
	s.push_back(CUTE(testNegativeIndexAccess));
	s.push_back(CUTE(testNegativeAtAccess));
	s.push_back(CUTE(testNegativeIndexAccess2));
	s.push_back(CUTE(testOutOfBoundException));
	s.push_back(CUTE(testFrontMethod));
	s.push_back(CUTE(testBackMethod));
	s.push_back(CUTE(testInitListCtor));
	s.push_back(CUTE(testEmptyMethodFromBase));
	s.push_back(CUTE(testAccessEmptySet));
	s.push_back(CUTE(testCopyCtor));
	s.push_back(CUTE(testGreaterComperator));
	s.push_back(CUTE(testLessComperator));
	s.push_back(CUTE(testGreaterForStringFunctor));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
