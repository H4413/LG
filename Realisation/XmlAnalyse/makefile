SOURCES += ../AnalyseurDTD/DTD.cpp
SOURCES += ../AnalyseurDTD/lex.yy.c
SOURCES += ../AnalyseurDTD/dtd.tab.c
SOURCES += ../AnalyseurXML/Xml.cpp
SOURCES += ../AnalyseurXML/lex.xx.c
SOURCES += ../AnalyseurXML/xml.tab.c

FLAGS = -g -DXXDEBUG=1 -DYYDEBUG=1 -DNDEBUG=1 -I../AnalyseurDTD/ -I../AnalyseurXML/


all: analyseDTD analyseXML 
	g++ $(FLAGS) -o analyse $(SOURCES)
	
analyseDTD:
	make -C ../AnalyseurDTD lex

analyseXML:
	make -C ../AnalyseurXML lex

clean:
	make -C ../AnalyseurDTD clean
	make -C ../AnalyseurXML clean

