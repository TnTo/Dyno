CXXFLAGS += -std=c++20 -Wall -I$(SOURCE_DIR)

SOURCE_DIR = src
BUILD_DIR = build
LIB_DIR = lib

TARGET = $(LIB_DIR)/dyno.a

TEST_SOURCE_DIR = tests
TEST_BUILD_DIR = tests/build
TEST_TARGET_DIR = tests/bin

TEST_MAIN = $(TEST_SOURCE_DIR)/test.cpp
TEST_MAIN_OBJ = $(TEST_BUILD_DIR)/test.o
TEST_MAIN_TARGET = $(TEST_TARGET_DIR)/test
TEST_TARGET = $(filter-out $(TEST_MAIN_TARGET),$(patsubst $(TEST_SOURCE_DIR)/%.cpp, $(TEST_TARGET_DIR)/%, $(wildcard $(TEST_SOURCE_DIR)/*.cpp)))

.PHONY : default test clean build

default : build

$(TARGET) : $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(wildcard $(SOURCE_DIR)/*.cpp))
	ar rcs $@ $^

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_BUILD_DIR)/%.o : $(TEST_SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

$(TEST_TARGET_DIR)/% : $(TEST_BUILD_DIR)/%.o $(TARGET) $(TEST_MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ 
	@./$@


build: $(TARGET)

test : $(TEST_TARGET)

clean:
	-rm $(TARGET)
	-rm -r $(BUILD_DIR)/*
	-rm -r $(TEST_TARGET_DIR)/*
	-rm -r $(TEST_BUILD_DIR)/*