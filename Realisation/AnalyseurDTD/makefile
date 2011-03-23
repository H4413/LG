all: analyseDTD
lex:
	flex  dtd.l
	bison  --debug --verbose --defines=yy.tab.h dtd.y	
analyseDTD: *.l *.y makefile lex
	g++ -g -DYYDEBUG=1 -o analyseDTD  lex.yy.c dtd.tab.c DTD.cpp -I../AnalyseurXML

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyseDTD

