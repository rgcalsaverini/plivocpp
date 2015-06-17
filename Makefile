INCLUDE=-I./include
LIB_DIR=./obj
BUILD_DIR=./build
LIB_NAME=plivocpp
CC_FLAGS := -Wall -Werror -std=c++11 -MMD
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix $(LIB_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -Wall -Werror -std=c++11 -L/usr/local/lib `pkg-config --libs --cflags curlpp`

all: shared

make_dirs: $(LIB_DIR) $(BUILD_DIR)
	@echo "Making build directories"

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)/lib
	@mkdir -p $(BUILD_DIR)/include

$(LIB_DIR)/%.o: src/%.cpp
	@echo "Compiling $@"
	$(CXX) $(CC_FLAGS) -fPIC -c -o $@ $< $(INCLUDE)

shared: make_dirs $(OBJ_FILES)
	@echo "Making shared lib..."
	$(CXX) -std=c++11 -shared -Wl,-soname,lib$(LIB_NAME).so.1 -o $(BUILD_DIR)/lib/lib$(LIB_NAME).so.1.0 $(OBJ_FILES)

install:
	@echo "Istalling..."
	@mkdir -p /usr/include/$(LIB_NAME)
	@cp -R ./include/*.hpp /usr/include/$(LIB_NAME)
	@cp $(BUILD_DIR)/lib/lib$(LIB_NAME).so.1.0 /usr/lib
	@ln -sf /usr/lib/lib$(LIB_NAME).so.1.0 /usr/lib/lib$(LIB_NAME).so
	@ln -sf /usr/lib/lib$(LIB_NAME).so.1.0 /usr/lib/lib$(LIB_NAME).so.1

uninstall:
	@echo "Uninstalling..."
	@rm -rf /usr/include/$(LIB_NAME)
	@rm /usr/lib/lib$(LIB_NAME).so.1.0
	@rm /usr/lib/lib$(LIB_NAME).so
	@rm /usr/lib/lib$(LIB_NAME).so.1

clean:
	@echo "Cleaning..."
	@rm -rf $(LIB_DIR)
	@rm -rf $(BUILD_DIR)

.PHONY: clean
