#makefile
#Set CFLAGS for debugging printing
EDEBUG= -DEDEBUG
DEBUG= -DDEBUG
BIN=YAPL.exe

#Set AUTORUN to auto run the program after compilation
AUTORUN= -DAUTORUN

YAPL.exe: parser.tab.o lex.yy.o
	gcc $(AUTORUN) parser.tab.c lex.yy.c -lfl -o $@ -w

parser.tab.o: parser.y
	bison -v -d parser.y
	#for debugging add -t to the command above

lex.yy.o: scanner.l
	flex scanner.l

debug: parser.tab.o lex.yy.o
	gcc $(EDEBUG) $(DEBUG) parser.tab.c lex.yy.c -lfl -o $(BIN) -w


clean: 
	rm parser.tab.* lex.yy.* YAPL.exe test
