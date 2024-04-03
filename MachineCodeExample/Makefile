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

TARGETS := test

all: $(TARGETS)

test: test.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<


clean:
	-rm -f *.o *~
	-rm -f $(TARGETS)
