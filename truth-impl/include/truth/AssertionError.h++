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

