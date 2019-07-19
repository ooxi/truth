#ifndef HEADER_TRUTH_BOOLEAN_SUBJECT
#define HEADER_TRUTH_BOOLEAN_SUBJECT


#include <truth/Fact.h++>
#include <truth/FailureMetadata.h++>
#include <truth/Subject.h++>





namespace truth {

	class BooleanSubject final : public Subject<bool> {
	public:
		explicit BooleanSubject(
			FailureMetadata& failureMetadata,
			bool const actual
		) :
			Subject<bool>{failureMetadata, actual}
		{}


		virtual ~BooleanSubject() {
		}


		void isTrue() {
			if (!getActual()) {
				failWithoutActual(Fact::simpleFact("expected to be true"));
			}
		}


		void isFalse() {
			if (getActual()) {
				failWithoutActual(Fact::simpleFact("expected to be false"));
			}
		}
	};
}



#endif

