CXXFLAGS += -std=c++20 -Wall -fmodules-ts

MODULE_DIR = gcm.cache
STD_MODULE_DIR = $(MODULE_DIR)/usr/include/c++/$(shell g++ --version | grep g++ | awk '{print $$3}')
SOURCE_DIR = src
BUILD_DIR = build
LIB_DIR = lib

MODULE_SOURCE = $(SOURCE_DIR)/dyno.cpp
MODULE_OBJECT = $(BUILD_DIR)/dyno.o
TARGET = $(LIB_DIR)/dyno.a

TEST_SOURCE_DIR = tests
TEST_BUILD_DIR = tests/build
TEST_TARGET_DIR = tests/bin

TEST_TARGET = $(patsubst $(TEST_SOURCE_DIR)/%.cpp, $(TEST_TARGET_DIR)/%, $(wildcard $(TEST_SOURCE_DIR)/*.cpp))

.PHONY : default test clean build
	
	.EXTRA_PREREQS = Makefile

default : build

$(TARGET) : $(MODULE_OBJECT)
	ar rcs $@ $^ $(BUILD_DIR)/model.o $(BUILD_DIR)/agent.o $(BUILD_DIR)/dyno.o


$(MODULE_DIR)/dyno.gcm $(BUILD_DIR)/dyno.o : $(SOURCE_DIR)/dyno.cpp $(MODULE_DIR)/dyno.model.gcm $(MODULE_DIR)/dyno.agent.gcm 
	$(CXX) $(CXXFLAGS) -c $< -o $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $<)

$(MODULE_DIR)/dyno.agent.gcm $(BUILD_DIR)/agent.o : $(SOURCE_DIR)/agent.cpp  
	$(CXX) $(CXXFLAGS) -c $< -o $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $<)

$(MODULE_DIR)/dyno.model.gcm $(BUILD_DIR)/model.o : $(SOURCE_DIR)/model.cpp $(STD_MODULE_DIR)/string.gcm 
	$(CXX) $(CXXFLAGS) -c $< -o $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $<)



$(STD_MODULE_DIR)/iostream.gcm :
	$(CXX) $(CXXFLAGS) -x c++-system-header iostream

$(STD_MODULE_DIR)/string.gcm :
	$(CXX) $(CXXFLAGS) -x c++-system-header string



$(TEST_BUILD_DIR)/model_creation.o : $(TEST_SOURCE_DIR)/model_creation.cpp $(MODULE_DIR)/dyno.gcm $(STD_MODULE_DIR)/iostream.gcm
	$(CXX) $(CXXFLAGS) -c $< -o $@ 



$(TEST_TARGET_DIR)/model_creation : $(TEST_BUILD_DIR)/model_creation.o $(TARGET)
	$(CXX) $(CXXFLAGS) $^ -o $@ 
	@echo TEST $@
	@./$@


Makefile : configure.py
	./configure.py
	$(MAKE) $(MAKECMDGOALS)

build: $(TARGET)

test : $(TEST_TARGET)

clean:
	rm -rf $(MODULE_DIR)
	rm -rf $(BUILD_DIR)/*
	rm -rf $(TEST_TARGET_DIR)/*
	rm -rf $(TEST_BUILD_DIR)/*