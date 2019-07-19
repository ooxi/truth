#include <cstdlib>
#include <truth/Truth.h++>

using truth::assert_;





static bool testHasLength() {
	assert_().that("my string").hasLength(9);

	try {
		assert_().that("12345").hasLength(4);

		return false;
	} catch (...) {
		return true;
	}
}



static bool testIsEmpty() {
	assert_().that("").isEmpty();

	try {
		assert_().that("a non empty string").isEmpty();

		return false;
	} catch (...) {
		return true;
	}
}



static bool testContains() {
	assert_().that("my string").contains("y s");

	try {
		assert_().that("my string").contains("a not contained string");

		return false;
	} catch (...) {
		return true;
	}
}





int main() {
	if (!testHasLength()) {
		return EXIT_FAILURE;
	}

	if (!testIsEmpty()) {
		return EXIT_FAILURE;
	}

	if (!testContains()) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

