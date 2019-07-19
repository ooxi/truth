#include <cstdlib>
#include <string>
#include <truth/Truth.h++>





int main() {

	try {
		truth::assert_().withMessage("my message").that(true).isFalse();
		return EXIT_FAILURE;

	} catch (truth::AssertionError const& error) {
		std::string const expected{"my message\nexpected to be false\n"};
		std::string const actual{error.what()};

		if (expected != actual) {
			return EXIT_FAILURE;
		}

	} catch (...) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

