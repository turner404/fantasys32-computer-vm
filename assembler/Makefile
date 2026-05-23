DEBUG=#-DDEBUG
GDB=#-g
STD=-std=c++17
all:
#	bison -d parser.yy -o parser.tab.cpp
#	flex -o lexer.cpp lexer.l
	g++ $(DEBUG) $(GDB) $(STD) src/lexer.cpp -c -o bin/lexer.o
	g++ $(DEBUG) $(GDB) $(STD) src/parser.tab.cpp -c -o bin/parser.o
# 	g++ $(DEBUG) $(GDB) $(STD) lexer_test.cpp lexer.o -o lexer_test
	g++ $(DEBUG) $(GDB) $(STD) src/ast.cpp -c -o bin/ast.o
	g++ $(DEBUG) $(GDB) $(STD) src/instructions.cpp -c -o bin/instructions.o
	g++ $(DEBUG) $(GDB) $(STD) src/assembler.cpp -c -o bin/assembler.o
	g++ $(DEBUG) $(GDB) $(STD) src/main.cpp bin/lexer.o bin/parser.o bin/assembler.o bin/ast.o bin/instructions.o -o assembler

