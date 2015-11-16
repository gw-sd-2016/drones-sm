#makefile
#Set CFLAGS for debugging printing
CFLAGS= -DEDEBUG# -DEDEBUG

#Set AUTOCOMPILE to auto run the program after compilation
#AUTOCOMPILE= -DAUTOCOMPILE

YAPL.exe: parser.tab.o lex.yy.o
	gcc $(CFLAGS) $(AUTOCOMPILE) parser.tab.c lex.yy.c -lfl -o $@ -w

parser.tab.o: parser.y
	bison -v -d parser.y
	#for debugging add -t to the command above

lex.yy.o: scanner.l
	flex scanner.l

clean: 
	rm parser.tab.* lex.yy.* YAPL.exe test
