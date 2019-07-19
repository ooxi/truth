#include <cstddef>
#include BUNDLE_INCLUDE





int main() {
	#ifndef HEADER_ROOT
	#error Missing HEADER_ROOT
	#endif

	#ifndef HEADER_INCLUDE_1
	#error Missing HEADER_INCLUDE_1
	#endif

	#ifndef HEADER_DIR_INCLUDE_2
	#error Missing HEADER_DIR_INCLUDE_2
	#endif

	return EXIT_SUCCESS;
}

