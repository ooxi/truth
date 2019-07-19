#include <cstdlib>
#include <truth/Fact.h++>
#include <truth/FailureMetadata.h++>
#include <truth/Subject.h++>
#include <truth/SubjectFactory.h++>
#include <truth/Truth.h++>





class MyType final {
private:
	int cookie;


public:
	explicit MyType(int cookie) : cookie{cookie} {
	}


	int getCookie() const {
		return cookie;
	}
};



class MyTypeSubject final : public truth::Subject<MyType> {
public:
	explicit MyTypeSubject(
		truth::FailureMetadata& failureMetadata,
		MyType actual
	) :
		truth::Subject<MyType>{failureMetadata, actual}
	{}


	virtual ~MyTypeSubject() {
	}


	void hasCookie(int const expectedCookie) {
		int const actualCookie = this->getActual().getCookie();

		if (expectedCookie != actualCookie) {
			failWithoutActual(truth::Fact::simpleFact("wrong cookie"));
		}
	}
};



class MyTypeSubjectFactory final : public truth::SubjectFactory<MyTypeSubject, MyType> {
public:
	virtual ~MyTypeSubjectFactory() {
	}


	[[nodiscard]] MyTypeSubject createSubject(
				truth::FailureMetadata failureMetadata,
				MyType actual
			) final override {

		return MyTypeSubject{failureMetadata, actual};
	}
};






int main() {
	truth::assert_().about(MyTypeSubjectFactory{}).that(MyType{42}).hasCookie(42);

	try {
		truth::assert_().about(MyTypeSubjectFactory{}).that(MyType{42}).hasCookie(13);
		return EXIT_FAILURE;
	} catch (...) {
		// expected
	}

	return EXIT_SUCCESS;
}

