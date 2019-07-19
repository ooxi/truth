#ifndef HEADER_TRUTH_SIMPLE_SUBJECT_BUILDER
#define HEADER_TRUTH_SIMPLE_SUBJECT_BUILDER


#include <truth/FailureMetadata.h++>
#include <truth/Subject.h++>
#include <truth/SubjectFactory.h++>





namespace truth {

	template<typename FailureMetadata, typename SubjectFactory>
	class SimpleSubjectBuilder final {
	private:
		FailureMetadata failureMetadata;
		SubjectFactory subjectFactory;


	public:
		explicit SimpleSubjectBuilder(
			FailureMetadata failureMetadata,
			SubjectFactory subjectFactory
		) :
			failureMetadata{failureMetadata},
			subjectFactory{subjectFactory}
		{}


		template<typename Actual>
		[[nodiscard]] auto that(Actual actual) {
			return subjectFactory.createSubject(failureMetadata, actual);
		}
	};
}



#endif

