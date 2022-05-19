all: compiler

OBJS = CodeGen.o \
		json.o  \
		AST.o  \
		parser.o \
		main.o	 \
		scanner.o \

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++17
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lncurses -rdynamic -L/usr/local/lib
LIBS = `$(LLVMCONFIG) --libs`

clean:
	$(RM) -rf parser.cpp parser.hpp test compiler scanner.cpp *.output $(OBJS)


CodeGen.cpp: CodeGen.h AST.h

AST.cpp: CodeGen.h AST.h

parser.cpp: parser.y
	bison -d -o $@ $<

parser.hpp: parser.cpp

scanner.cpp: scanner.l parser.hpp
	flex -o $@ $<

%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $<

lex: parser.o scanner.o
	g++ $(CPPFLAGS) -o $@ parser.o scanner.o $(LIBS) $(LDFLAGS)

compiler: $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

test: compiler test.input
	cat test.input | ./compiler

# testlink: output.o testmain.cpp
# 	clang output.o testmain.cpp -o test
# 	./test
