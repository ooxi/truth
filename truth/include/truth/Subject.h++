#ifndef HEADER_TRUTH_SUBJECT
#define HEADER_TRUTH_SUBJECT


#include <sstream>
#include <string>
#include <truth/Fact.h++>
#include <truth/FailureMetadata.h++>





namespace truth {

	template<typename Actual>
	class Subject {
	private:
		FailureMetadata failureMetadata;
		Actual actual;


	protected:
		explicit Subject(
			FailureMetadata failureMetadata,
			Actual actual
		) :
			failureMetadata{failureMetadata},
			actual{actual}
		{}


		virtual ~Subject() {
		}


		[[nodiscard]] FailureMetadata& getFailureMetadata() {
			return failureMetadata;
		}


		[[nodiscard]] Actual const& getActual() const {
			return actual;
		}


		void failWithoutActual(Fact check) {
			getFailureMetadata()
				.withFact(check)
				.fail();
		}


		void failWithActual(Fact check) {
			std::stringstream buf;
			buf << actual;

			getFailureMetadata()
				.withFact(check)
				.withFact(Fact::fact("but was", buf.str()))
				.fail();
		}


	public:

		template<typename Expected>
		void isEqualTo(Expected const expected);

		template<typename Expected>
		void isNotEqualTo(Expected const expected);
	};
}



#endif

