#ifndef HEADER_TRUTH_ASSERTION_ERROR_FACTORY
#define HEADER_TRUTH_ASSERTION_ERROR_FACTORY


#include <algorithm>
#include <cstddef>
#include <sstream>
#include <truth/AssertionError.h++>
#include <truth/Fact.h++>
#include <truth/LazyMessage.h++>
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

