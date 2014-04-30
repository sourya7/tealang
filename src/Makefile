
CC=clang++
CFLAGS=-std=c++11
all:
	$(CC) $(CFLAGS) TLang.cxx Parser.cxx Lexer.cxx ExprAST.cxx IfStmtAST.cxx IRBuilder.cxx NodeAST.cxx SeqAST.cxx TObject.cxx
clean:
	rm -f a.out *.o
run:
	./a.out current.test
