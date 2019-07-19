#include <cstdlib>
#include <truth/Truth.h++>

using truth::assert_;





static bool testIsTrue() {
	assert_().that(true).isTrue();

	try {
		assert_().that(false).isTrue();
		return false;

	} catch (...) {
		return true;
	}
}



static bool testIsFalse() {
	assert_().that(false).isFalse();

	try {
		assert_().that(true).isFalse();
		return false;

	} catch (...) {
		return true;
	}
}





int main() {
	if (!testIsTrue()) {
		return EXIT_FAILURE;
	}

	if (!testIsFalse()) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

