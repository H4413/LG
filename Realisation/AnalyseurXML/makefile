all: analyseXML
analyseXML: *.l *.y makefile
	flex  xml.l
	bison --debug --verbose --defines=yy.tab.h xml.y
	g++ -g -DYYDEBUG=1 -o analyseXML  lex.yy.c  Xml.cpp xml.tab.c -I ../AnalyseDTD 
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyseXML

