#ifndef HEADER_TRUTH_SUBJECT_FACTORY
#define HEADER_TRUTH_SUBJECT_FACTORY


#include <truth/FailureMetadata.h++>
#include <truth/Subject.h++>





namespace truth {

	template<typename Subject,  typename Actual>
	class SubjectFactory {
	public:
		virtual ~SubjectFactory() {
		}


		[[nodiscard]] virtual Subject createSubject(
				FailureMetadata failureMetadata,
				Actual actual
			);
	};
}



#endif

