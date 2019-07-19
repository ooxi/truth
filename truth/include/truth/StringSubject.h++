#ifndef HEADER_TRUTH_STRING_SUBJECT
#define HEADER_TRUTH_BOOLEAN_SUBJECT


#include <cstddef>
#include <string>
#include <truth/Fact.h++>
#include <truth/FailureMetadata.h++>
#include <truth/Subject.h++>





namespace truth {

	class StringSubject final : public Subject<std::string> {
	public:
		explicit StringSubject(
			FailureMetadata& failureMetadata,
			std::string const actual
		) :
			Subject<std::string>{failureMetadata, actual}
		{}


		virtual ~StringSubject() {
		}


		void hasLength(std::size_t const expectedLength) {
			std::size_t const actualLength = getActual().length();

			if (expectedLength != actualLength) {
				getFailureMetadata()
					.withFact(Fact::fact("value of", "string.length()"))
					.withFact(Fact::fact("expected", std::to_string(expectedLength)))
					.withFact(Fact::fact("but was", std::to_string(actualLength)))
					.withFact(Fact::fact("string was", getActual()))
					.fail();
			}
		}


		void isEmpty() {
			if (!getActual().empty()) {
				failWithActual(Fact::simpleFact("expected to be empty"));
			}
		}


		void contains(std::string str) {
			if (std::string::npos == getActual().find(str)) {
				failWithActual(Fact::fact("expected to contain", str));
			}
		}
	};
}



#endif

