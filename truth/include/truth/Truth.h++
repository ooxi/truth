#line 1 "truth/Truth.h++"
#ifndef HEADER_TRUTH_TRUTH
#define HEADER_TRUTH_TRUTH


#line 1 "truth/FailureMetadata.h++"
#ifndef HEADER_TRUTH_FAILURE_METADATA
#define HEADER_TRUTH_FAILURE_METADATA


#include <sstream>
#include <string>
#line 1 "truth/AssertionErrorFactory.h++"
#ifndef HEADER_TRUTH_ASSERTION_ERROR_FACTORY
#define HEADER_TRUTH_ASSERTION_ERROR_FACTORY


#include <algorithm>
#include <cstddef>
#include <sstream>
#line 1 "truth/AssertionError.h++"
#ifndef HEADER_TRUTH_ASSERTION_ERROR
#define HEADER_TRUTH_ASSERTION_ERROR


#include <exception>
#include <string>





namespace truth {

	class AssertionError final : public std::exception {
	private:
		std::string message;

	public:
		explicit AssertionError(std::string message) : message{message} {
		}


		virtual char const* what() const noexcept final override {
			return message.c_str();
		}
	};
}



#endif

#line 9 "truth/AssertionErrorFactory.h++"
#line 1 "truth/Fact.h++"
#ifndef HEADER_TRUTH_FACT
#define HEADER_TRUTH_FACT


#include <optional>
#include <string>





namespace truth {

	class Fact final {
	private:
		std::string key;
		std::optional<std::string> value;


	private:
		explicit Fact(
			std::string key,
			std::optional<std::string> value
		) :
			key{key},
			value{value}
		{}


	public:
		static Fact fact(std::string key, std::optional<std::string> value) {
			return Fact{key, value};
		}

		static Fact simpleFact(std::string key) {
			return Fact{key, std::nullopt};
		}


	public:
		std::string const& getKey() const {
			return key;
		}

		bool hasValue() const {
			return value.has_value();
		}

		std::string const& getValue() const {
			return value.value();
		}
	};
}



#endif

#line 10 "truth/AssertionErrorFactory.h++"
#line 1 "truth/LazyMessage.h++"
#ifndef HEADER_TRUTH_LAZY_MESSAGE
#define HEADER_TRUTH_LAZY_MESSAGE


#include <ostream>
#include <string>





namespace truth {

	/**
	 * Currently not really a lazy message, but might be extended to store
	 * arguments to be forwarded to {@link std::format} in the future
	 */
	class LazyMessage final {
	private:
		std::string message;


	public:
		explicit LazyMessage(std::string const& message) : message{message} {
		}


		std::string const& getMessage() const {
			return message;
		}
	};



	std::ostream& operator<<(std::ostream& os, LazyMessage const& lazyMessage) {
		return os << lazyMessage.getMessage();
	}
}



#endif

#line 11 "truth/AssertionErrorFactory.h++"
#include <vector>





namespace truth {

	/**
	 * @see https://github.com/google/truth/blob/master/core/src/main/java/com/google/common/truth/Fact.java#L87
	 */
	class AssertionErrorFactory final {
	public:

		static AssertionError createAssertionError(
					std::vector<LazyMessage> const& messages,
					std::vector<Fact> const& facts
				) {

			std::stringstream buf;
			std::size_t longestKeyLength{0};


			for (auto const& fact : facts) {
				if (fact.hasValue()) {
					longestKeyLength = std::max(
						longestKeyLength,
						fact.getKey().length()
					);
				}
			}


			for (auto const& message : messages) {
				buf << message << "\n";
			}


			if (messages.empty()) {
				buf << "\n";
			}


			for (auto const& fact : facts) {
				buf << fact.getKey();

				if (fact.hasValue()) {
					for (	std::size_t length{fact.getKey().length()};
						length < longestKeyLength;
						++length
					) {
						buf << " ";
					}

					buf << ": " << fact.getValue();
				}
				buf << "\n";
			}


			return AssertionError{buf.str()};
		}



	private:
		explicit AssertionErrorFactory() = delete;
	};	
}



#endif

#line 8 "truth/FailureMetadata.h++"
#line 9 "truth/FailureMetadata.h++"
#line 1 "truth/FailureStrategy.h++"
#ifndef HEADER_TRUTH_FAILURE_STRATEGY
#define HEADER_TRUTH_FAILURE_STRATEGY


#line 6 "truth/FailureStrategy.h++"





namespace truth {

	class FailureStrategy {
	public:
		virtual ~FailureStrategy() {
		}


		virtual void fail(AssertionError const failure) = 0;
	};
}



#endif

#line 10 "truth/FailureMetadata.h++"
#line 11 "truth/FailureMetadata.h++"
#include <vector>





namespace truth {

	class FailureMetadata final {
	private:
		FailureStrategy& failureStrategy;
		std::vector<LazyMessage> const messages;
		std::vector<Fact> const facts;


	public:
		explicit FailureMetadata(
			FailureStrategy& failureStrategy,
			std::vector<LazyMessage> messages,
			std::vector<Fact> facts
		) :
			failureStrategy{failureStrategy},
			messages{messages},
			facts{facts}
		{}


		[[nodiscard]] auto withMessage(std::string message) {
			std::vector<LazyMessage> copyOfMessages{messages};
			copyOfMessages.emplace_back(message);

			return FailureMetadata{failureStrategy, copyOfMessages, facts};
		}


		[[nodiscard]] auto withFact(Fact fact) {
			std::vector<Fact> copyOfFacts{facts};
			copyOfFacts.push_back(fact);

			return FailureMetadata{failureStrategy, messages, copyOfFacts};
		}


		void fail() {
			auto const error = AssertionErrorFactory::createAssertionError(
				messages, facts
			);
			failureStrategy.fail(error);
		}
	};
}



#endif

#line 6 "truth/Truth.h++"
#line 1 "truth/StandardSubjectBuilder.h++"
#ifndef HEADER_TRUTH_STANDARD_SUBJECT_BUILDER
#define HEADER_TRUTH_STANDARD_SUBJECT_BUILDER


#include <string>
#line 1 "truth/BooleanSubject.h++"
#ifndef HEADER_TRUTH_BOOLEAN_SUBJECT
#define HEADER_TRUTH_BOOLEAN_SUBJECT


#line 6 "truth/BooleanSubject.h++"
#line 7 "truth/BooleanSubject.h++"
#line 1 "truth/Subject.h++"
#ifndef HEADER_TRUTH_SUBJECT
#define HEADER_TRUTH_SUBJECT


#include <sstream>
#include <string>
#line 8 "truth/Subject.h++"
#line 9 "truth/Subject.h++"


// hallo


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

#line 8 "truth/BooleanSubject.h++"





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

#line 7 "truth/StandardSubjectBuilder.h++"
#line 8 "truth/StandardSubjectBuilder.h++"
#line 1 "truth/SimpleSubjectBuilder.h++"
#ifndef HEADER_TRUTH_SIMPLE_SUBJECT_BUILDER
#define HEADER_TRUTH_SIMPLE_SUBJECT_BUILDER


#line 6 "truth/SimpleSubjectBuilder.h++"
#line 7 "truth/SimpleSubjectBuilder.h++"
#line 1 "truth/SubjectFactory.h++"
#ifndef HEADER_TRUTH_SUBJECT_FACTORY
#define HEADER_TRUTH_SUBJECT_FACTORY


#line 6 "truth/SubjectFactory.h++"
#line 7 "truth/SubjectFactory.h++"





namespace truth {

	template<typename Subject,  typename Actual>
	class SubjectFactory {
	public:
		virtual ~SubjectFactory() {
		}


		[[nodiscard]] virtual Subject createSubject(
				FailureMetadata failureMetadata,
				Actual actual
			) = 0;
	};
}



#endif

#line 8 "truth/SimpleSubjectBuilder.h++"





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

#line 9 "truth/StandardSubjectBuilder.h++"
#line 1 "truth/StringSubject.h++"
#ifndef HEADER_TRUTH_STRING_SUBJECT
#define HEADER_TRUTH_BOOLEAN_SUBJECT


#include <cstddef>
#include <string>
#line 8 "truth/StringSubject.h++"
#line 9 "truth/StringSubject.h++"
#line 10 "truth/StringSubject.h++"





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

#line 10 "truth/StandardSubjectBuilder.h++"
#line 11 "truth/StandardSubjectBuilder.h++"





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

#line 7 "truth/Truth.h++"
#line 1 "truth/ThrowAssertionErrorFailureStrategy.h++"
#ifndef HEADER_TRUTH_THROW_ASSERTION_ERROR_FAILURE_STRATEGY
#define HEADER_TRUTH_THROW_ASSERTION_ERROR_FAILURE_STRATEGY


#line 6 "truth/ThrowAssertionErrorFailureStrategy.h++"





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


#line 8 "truth/Truth.h++"





namespace truth {

	[[nodiscard]] auto assert_() {
		static ThrowAssertionErrorFailureStrategy failureStrategy;
		return StandardSubjectBuilder{FailureMetadata{failureStrategy, {}, {}}};
	}
}



#endif

