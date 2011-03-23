all: analyseXML
lex:
	flex  -P xx xml.l
	bison --debug --verbose -p xx --defines=xx.tab.h xml.y
analyseXML: *.l *.y makefile lex
	g++ -g -DXXDEBUG=1 -o analyseXML lex.xx.c  Xml.cpp xml.tab.c -I../AnalyseurDTD/
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyseXML
