# beta-core-test
A C++11 Test Suite that aims to use native c++11 code with out the need for macros. Just extend the test class.



## Compilation
gnu make file, cd to project folder and run `make`. 

## Usage 
Currently only class based testing is supported.

### Simple Test class
```c++
#include "test.hpp"

class TestSomething: public betacore::test::Test{

	void function(){
		// assert
		this->assert_true(true);
	}
	TestSomething(){
		// Add function to test queue
		this->enqueue(std::bind(&function, this),"name of test");
		// run the test queue
		this->run();
	}
}
```
* When adding to the queue the [std::bind](https://en.cppreference.com/w/cpp/utility/functional/bind) function must be called to map instance data in the class to the test case. 
* To compile you need to link the .so file (.dll for win) in the compiler.

### GCC
* you need to include the folder with header file with `-I <path>/`
* you need to state the `<path>/beta_core_test.so` location

```make
g++ <other args> -I <path to folder with header file>  <path to beta_core_test.so> my-test.cpp -o my-test.out
```
See the `makefile sample:` for working example