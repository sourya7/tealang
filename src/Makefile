
CC=clang++
CFLAGS=-std=c++11 -m32 -ggdb
all:
	$(CC) $(CFLAGS) TLang.cxx Parser.cxx Lexer.cxx ExprAST.cxx IfStmtAST.cxx IRBuilder.cxx NodeAST.cxx SeqAST.cxx Object.cxx VM.cxx
clean:
	rm -f a.out *.o
run:
	./a.out current.test
