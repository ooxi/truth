#ifndef HEADER_TRUTH_TRUTH
#define HEADER_TRUTH_TRUTH


#include <truth/FailureMetadata.h++>
#include <truth/StandardSubjectBuilder.h++>
#include <truth/ThrowAssertionErrorFailureStrategy.h++>





namespace truth {

	[[nodiscard]] auto assert_() {
		static ThrowAssertionErrorFailureStrategy failureStrategy;
		return StandardSubjectBuilder{FailureMetadata{failureStrategy, {}, {}}};
	}
}



#endif

