#ifndef HEADER_TRUTH_FAILURE_METADATA
#define HEADER_TRUTH_FAILURE_METADATA


#include <sstream>
#include <string>
#include <truth/AssertionErrorFactory.h++>
#include <truth/Fact.h++>
#include <truth/FailureStrategy.h++>
#include <truth/LazyMessage.h++>
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

