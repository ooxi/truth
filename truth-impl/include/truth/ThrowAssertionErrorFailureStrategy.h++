#ifndef HEADER_TRUTH_THROW_ASSERTION_ERROR_FAILURE_STRATEGY
#define HEADER_TRUTH_THROW_ASSERTION_ERROR_FAILURE_STRATEGY


#include <truth/FailureStrategy.h++>





namespace truth {

	class ThrowAssertionErrorFailureStrategy final : public FailureStrategy {
	public:
		virtual ~ThrowAssertionErrorFailureStrategy() {
		}


		void fail(AssertionError const failure) final override {
			throw failure;
		}
	};
}



#endif


