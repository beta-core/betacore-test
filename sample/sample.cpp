#include <betacore/test.hpp>

class Sample : public betacore::test::Test
{
public:
	void test_bad()
	{
		const char *hi = "hi";
		this->assert_null(hi);
		this->assert_true(true); // will not run
	}
	void test_not_null()
	{
		const char *hi = "hi";
		this->assert_not_null(hi);
	}
	void test_null()
	{
		auto a = nullptr;
		this->assert_null(a);
	}
	void test_greater_than()
	{
		this->assert_greater_than(2, 1);
	}
	void test_greater_than_equal()
	{
		this->assert_greater_than_or_equal(2, 2);
	}
	void test_less_than()
	{
		this->assert_less_than(1, 2);
	}
	void test_less_than_equal()
	{
		this->assert_less_than_or_equal(1, 1);
	}
	void test_equal()
	{
		this->assert_equal(1, 1);
	}
	void test_not_equal()
	{
		this->assert_not_equal(1, -1);
	}
	Sample()
	{
		this->enqueue(std::bind(&Sample::test_null, this), "test_null");
		this->enqueue(std::bind(&Sample::test_not_null, this), "test_not_null");
		this->enqueue(std::bind(&Sample::test_bad, this), "test_bad");
		this->enqueue(std::bind(&Sample::test_greater_than, this), "test_greater_than");
		this->enqueue(std::bind(&Sample::test_greater_than_equal, this), "test_greater_than_equal");
		this->enqueue(std::bind(&Sample::test_less_than, this), "test_less_than");
		this->enqueue(std::bind(&Sample::test_less_than_equal, this), "test_less_than_equal");
		this->enqueue(std::bind(&Sample::test_equal, this), "test_equal");
		this->enqueue(std::bind(&Sample::test_not_equal, this), "test_not_equal");
		this->run();
	}
	~Sample() {}
};
int main(int argc, char *argv[])
{
	return Sample().exit();
}