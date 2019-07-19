#ifndef HEADER_TRUTH_FAILURE_STRATEGY
#define HEADER_TRUTH_FAILURE_STRATEGY


#include <truth/AssertionError.h++>





namespace truth {

	class FailureStrategy {
	public:
		virtual ~FailureStrategy() {
		}


		virtual void fail(AssertionError const failure) = 0;
	};
}



#endif

