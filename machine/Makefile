CXX := g++
CXXFLAGS := -Wall -std=c++11 -Wpedantic -Wextra -Werror -g
LDFLAGS :=
#OPENGL_LDFLAGS := -lglut -lGLU -lGL

UNAME := $(shell uname)

# OS X specific options
ifeq ($(UNAME), Darwin)
OPENGL_LDFLAGS := -framework OpenGL -framework GLUT
CXXFLAGS := $(CXXFLAGS) -Wno-deprecated
endif

TARGETS := instructions_tester

run: instructions_tester
	./instructions_tester


instructions_tester: InstructionsTester.o Instructions.o
	$(CXX) $(CXXFLAGS) -o $@ $^

InstructionsTester.o: InstructionsTester.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Instructions.o: Instructions.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<


clean:
	-rm -f *.o *~
	-rm -f $(TARGETS)
