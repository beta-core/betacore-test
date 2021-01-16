#include "test.hpp"
namespace betacore::test
{

void Test::set_up() {}
void Test::tear_down() {}
Test::Test()
{
	this->set_up();
}
Test::~Test()
{
	this->tear_down();
}
void Test::verify(bool condition, std::string message, std::string method)
{
	if (!condition)
		throw AssertException(message, method);
	this->_passed_asserts.push_back(method + " :: " + message);
}
void Test::run()
{
	std::cout << "Starting Unit Tests" << this->current << std::endl;
	for (auto item : this->_queue)
	{
		this->current = item.second;
		try
		{
			this->_passed_asserts.clear();
			std::cout << "Running Test: " << this->current << std::endl;
			auto fn = item.first;
			fn();
		}
		catch (AssertException e)
		{
			e.summary();
			this->failed.insert(this->current);
			continue;
		}
		catch (std::exception e)
		{
			// well test failed...
			// AssertException("Uncought Exception", this->current);
			this->print_test_summary();
			std::cout << "\tUncought Exception :: " << this->current << std::endl;
			std::cout << "\t" << e.what() << std::endl;
			this->failed.insert(this->current);
			continue;
		}
		this->print_test_summary();
		this->passed.insert(this->current);
	}
	this->summary();
}


void Test::print_test_summary()
{
	for (auto assert : this->_passed_asserts)
	{
		std::cout << "\tPassed :: " << assert << std::endl;
	}
}
void Test::print_failed()
{
	std::cout << "Failed :: "
			  << this->failed.size()
			  << " :: "
			  << this->failed_percent()
			  << "%"
			  << std::endl;
	for (auto a : this->failed)
	{
		std::cout << "\t" << a << std::endl;
	}
}


const std::size_t Test::exit(){
	return this->failed.size();
}

double Test::failed_percent()
{
	return 100 - this->passed_percent();
}
double Test::passed_percent()
{
	if (this->_queue.size() == 0)
		return 0;
	return ((double)this->passed.size() / this->_queue.size() * 100);
}

void Test::print_passed()
{

	std::cout << "Passed :: "
			  << this->passed.size()
			  << " :: "
			  << this->passed_percent()
			  << "%"
			  << std::endl;
	for (auto a : this->passed)
	{
		std::cout << "\t" << a << std::endl;
	}
}
void Test::summary()
{
	this->print_failed();
	this->print_passed();
}

bool Test::current_failed()
{
	return this->failed.find(this->current) !=
		   this->failed.end();
}

void Test::stats()
{
	std::cout << "test" << std::endl;
}

AssertException::AssertException(const std::string message) : _message(message), _method("???") {}
AssertException::AssertException(const std::string message, const std::string method) : _message(message), _method(method) {}
AssertException::AssertException() : _message("Probelm with Assertion"), _method("???") {}

const char *AssertException::what() const throw()
{
	return this->_message.c_str();
}

void AssertException::summary()
{
	std::cout << "\tFailed :: " << this->_method << " :: " << this->_message << std::endl;
}
} // namespace betacore::test
