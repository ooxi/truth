#include <cstdlib>
#include <truth/Truth.h++>

using truth::assert_;





int main() {
	assert_().that(true).isTrue();

	try {
		assert_().that(false).isTrue();
		return EXIT_FAILURE;
	} catch (...) {
		// Success
	}

	return EXIT_SUCCESS;
}

