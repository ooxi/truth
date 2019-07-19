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

