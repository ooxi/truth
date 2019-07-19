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

