#ifndef HEADER_TRUTH_STANDARD_SUBJECT_BUILDER
#define HEADER_TRUTH_STANDARD_SUBJECT_BUILDER


#include <string>
#include <truth/BooleanSubject.h++>
#include <truth/FailureMetadata.h++>
#include <truth/SimpleSubjectBuilder.h++>
#include <truth/StringSubject.h++>
#include <truth/SubjectFactory.h++>





namespace truth {

	class StandardSubjectBuilder final {
	private:
		FailureMetadata failureMetadata;


	public:
		explicit StandardSubjectBuilder(
			FailureMetadata failureMetadata
		) :
			failureMetadata{failureMetadata}
		{}


		void fail();


		template<typename SubjectFactory>
		[[nodiscard]] auto about(SubjectFactory subjectFactory) {
			return SimpleSubjectBuilder{failureMetadata, subjectFactory};
		}


		[[nodiscard]] auto withMessage(std::string message) {
			return StandardSubjectBuilder{failureMetadata.withMessage(message)};
		}


		[[nodiscard]] auto that(bool actual) {
			return BooleanSubject{failureMetadata, actual};
		}


		[[nodiscard]] auto that(std::string actual) {
			return StringSubject{failureMetadata, actual};
		}


		[[nodiscard]] auto that(char const* actual) {
			return that(std::string{actual});
		}
	};
}



#endif

