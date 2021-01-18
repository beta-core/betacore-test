NAME=libbetacoretest
OUTPUT_DIR= bin
COMPILER = g++
FLAGS =-W -ggdb -std=c++11 -fsanitize=address
LIBRARY_FLAGS= -std=c++11 -c -fPIC -shared
SOURCE_DIR = source/
HEADERS_DIR = include/
INC = -I $(HEADERS_DIR)
VERSION_MAJOR=1
VERSION_MINOR=0
VERSION_PATCH=0
VERSION=$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)

all: clean test sample

test: $(SOURCE_DIR)test.cpp | make_dir
	$(COMPILER)  $(LIBRARY_FLAGS) $(INC) $(SOURCE_DIR)test.cpp -o $(OUTPUT_DIR)/$(NAME).so.$(VERSION)
sample: sample/sample.cpp | test 
	$(COMPILER) $(FLAGS) $(INC) $(NAME).so.$(VERSION) sample/sample.cpp -o $(OUTPUT_DIR)/sample.out
clean: make_dir
	rm -f $(OUTPUT_DIR)/*.so && rm -f $(OUTPUT_DIR)/*.out && rm -f $(OUTPUT_DIR)/*.o
make_dir:
	mkdir -p $(OUTPUT_DIR)
install:
	mkdir -p /usr/include/betacore/ && \
	mkdir -p /usr/lib/betacore &&  \
	cp include/test.hpp /usr/include/betacore/. &&  \
	cp bin/$(NAME).so.$(VERSION) /usr/lib/betacore/.
symlink: 
	ln -s /usr/lib/betacore/$(NAME).so.$(VERSION) /usr/lib/betacore/ $(NAME).so.$(VERSION_MAJOR) && \
	ln -s /usr/lib/betacore/$(NAME).so.$(VERSION_MAJOR)/usr/lib/betacore/ $(NAME).so