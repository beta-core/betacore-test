#ifndef __BETACORE_UTIL_test_HPP__
#define __BETACORE_UTIL_test_HPP__
#include <typeinfo>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <utility>
#include <set>
#include <thread>

/**
 * betacore.org
 * 	Test Framework
 */
namespace betacore::test
{

class AssertException : public std::exception
{
private:
	const std::string _message;
	const std::string _method;

public:
	AssertException(const std::string message, const std::string method);
	AssertException(const std::string message);
	AssertException();
	const char *what() const throw();
	void summary();
};

class Test
{
private:
	std::vector<std::string> _passed_asserts;
	std::string current;
	std::set<std::string> passed;
	std::set<std::string> failed;
	std::vector<std::pair<std::function<void()>, std::string>> _queue;
	bool current_failed();

protected:
	/**
	 * Enqueue function into the test
	 *
	 * Arguments:
	 *
	 * 		function(Fn): function pointer
	 * 		name(std::string): name of test case
	 */
	template <typename Fn>
	void enqueue(Fn function, std::string name)
	{
		this->_queue.push_back(std::make_pair(function, name));
	}

	void verify(bool condition, std::string message, std::string method);

public:
	Test();
	~Test();

	/**
	 * run the queue
	 */
	void run();

	/**
	 * Function to setup classes
	 */
	void set_up();

	/**
	 * Teardown called in decontrustion
	 */
	void tear_down();

	void print_failed();
	void print_passed();
	void print_test_summary();
	void summary();
	void stats();

	/*
	 * Exit code
	 */
	const std::size_t exit();

	double failed_percent();
	double passed_percent();

	template <typename Null_Type>
	void assert_null(Null_Type type)
	{
		this->verify(type == nullptr, "Should be null", "assert_null");
	}
	template <typename Null_Type>
	void assert_not_null(Null_Type type)
	{
		this->verify(type != nullptr, "Should not be null", "assert_not_null");
	}

	template <typename A>
	void assert_true(const A &a)
	{
		this->verify(a, "value is true", "assert_true");
	}
	template <typename A>
	void assert_false(const A &a)
	{
		this->verify(!a, "value is false", "assert_false");
	}
	/**
	 * Boolean Compair of a and b
	 */
	template <typename A>
	void assert_equal(const A &a, const A &b)
	{
		this->assert_equal(a, b, "Assert Equals");
	}

	template <typename A>
	void assert_equal(const A &a, const A &b, std::string message)
	{
		this->verify(a == b, message, "assert_equal");
	}
	template <typename Q, typename B>
	void assert_equal(const Q &a, const B &b)
	{
		this->assert_equal(a, b, "Assert Equals");
	}

	template <typename Q, typename B>
	void assert_equal(const Q &a, const B &b, std::string message)
	{
		this->verify(a == b, message, "assert_equal");
	}

	template <typename A>
	void assert_not_equal(const A &a, const A &b)
	{
		this->assert_not_equal(a, b, "Assert Equals");
	}

	template <typename A>
	void assert_not_equal(const A &a, const A &b, std::string message)
	{
		this->verify(a != b, message, "assert_not_equal");
	}
	template <typename Q, typename B>
	void assert_not_equal(const Q &a, const B &b)
	{
		this->assert_not_equal(a, b, "Assert Equals");
	}

	template <typename Q, typename B>
	void assert_not_equal(const Q &a, const B &b, std::string message)
	{
		this->verify(a != b, message, "assert_not_equal");
	}
	template <typename A>
	void assert_greater_than(const A &a, const A &b)
	{
		this->assert_greater_than(a, b, "Assert Equals");
	}

	template <typename A>
	void assert_greater_than(const A &a, const A &b, std::string message)
	{
		this->verify(a > b, message, "assert_greater_than");
	}
	template <typename Q, typename B>
	void assert_greater_than(const Q &a, const B &b)
	{
		this->assert_greater_than(a, b, "Assert Equals");
	}

	template <typename Q, typename B>
	void assert_greater_than(const Q &a, const B &b, std::string message)
	{
		this->verify(a > b, message, "assert_greater_than");
	}

	template <typename A>
	void assert_greater_than_or_equal(const A &a, const A &b)
	{
		this->assert_greater_than_or_equal(a, b, "Assert Equals");
	}

	template <typename A>
	void assert_greater_than_or_equal(const A &a, const A &b, std::string message)
	{
		this->verify(a >= b, message, "assert_greater_than_or_equal");
	}
	template <typename Q, typename B>
	void assert_greater_than_or_equal(const Q &a, const B &b)
	{
		this->assert_greater_than_or_equal(a, b, "Assert Equals");
	}

	template <typename Q, typename B>
	void assert_greater_than_or_equal(const Q &a, const B &b, std::string message)
	{
		this->verify(a >= b, message, "assert_greater_than_or_equal");
	}

	template <typename A>
	void assert_less_than_or_equal(const A &a, const A &b)
	{
		this->assert_less_than_or_equal(a, b, "Assert Equals");
	}

	template <typename A>
	void assert_less_than_or_equal(const A &a, const A &b, std::string message)
	{
		this->verify(a <= b, message, "assert_less_than_or_equal");
	}
	template <typename Q, typename B>
	void assert_less_than_or_equal(const Q &a, const B &b)
	{
		this->assert_less_than_or_equal(a, b, "Assert Equals");
	}

	template <typename Q, typename B>
	void assert_less_than_or_equal(const Q &a, const B &b, std::string message)
	{
		this->verify(a <= b, message, "assert_less_than_or_equal");
	}

	template <typename A>
	void assert_less_than(const A &a, const A &b)
	{
		this->assert_less_than(a, b, "Assert Equals");
	}

	template <typename A>
	void assert_less_than(const A &a, const A &b, std::string message)
	{
		this->verify(a < b, message, "assert_less_than");
	}
	template <typename Q, typename B>
	void assert_less_than(const Q &a, const B &b)
	{
		this->assert_less_than(a, b, "Assert Equals");
	}

	template <typename Q, typename B>
	void assert_less_than(const Q &a, const B &b, std::string message)
	{
		this->verify(a < b, message, "assert_less_than");
	}
};

} // namespace betacore::test
#endif