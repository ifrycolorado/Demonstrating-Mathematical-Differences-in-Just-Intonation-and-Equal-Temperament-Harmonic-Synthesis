TARGET = FP
SRC_FILES = main.cpp io_functions.cpp SineWave.cpp SynthWave.cpp Wave.cpp

CXX = g++
CFLAGS = -Wall -g -std=c++11

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CFLAGS) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)

# DEPENDENCIES
# test_suite.o: test_suite.cpp test_suite.h linked_list_functions.cpp linked_list_functions.h Node.h
# linked_list_functions.o: linked_list_functions.cpp linked_list_functions.h Node.h
# main.o: main.cpp test_suite.h Node.h