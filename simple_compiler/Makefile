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

TARGETS := simple_compiler symbol_test

all: $(TARGETS)

run: simple_compiler
	./simple_compiler

Node.o: Node.cpp Node.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

symbol_test: symbol_test.o Symbol.o
	$(CXX) $(CXXFLAGS) -o $@ $^

symbol_test.o: symbol_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Symbol.o: Symbol.cpp Symbol.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

#simple_compiler: main.o Token.o StateMachine.o Scanner.o Symbol.o Parser.o Node.o
#	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(OPENGL_LDFLAGS)

simple_compiler: main.o Token.o StateMachine.o Scanner.o Symbol.o Parser.o Node.o Instructions.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: Main.cpp Token.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Token.o: Token.cpp Token.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

StateMachine.o: StateMachine.cpp StateMachine.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Scanner.o: Scanner.cpp Scanner.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Parser.o: Parser.cpp Parser.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

InstructionsTester.o: InstructionsTester.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Instructions.o: Instructions.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	-rm -f *.o *~
	-rm -f $(TARGETS)
