SOURCES += AnalyseurDTD/DTD.cpp
SOURCES += AnalyseurDTD/lex.yy.c
SOURCES += AnalyseurDTD/dtd.tab.c
SOURCES += AnalyseurXML/Xml.cpp
SOURCES += AnalyseurXML/lex.xx.c
SOURCES += AnalyseurXML/xml.tab.c
SOURCES += Xslt/XslTransform.cpp
SOURCES += analyser.cpp

FLAGS = -g -DXXDEBUG=1 -DYYDEBUG=1 -DNDEBUG=1 -IAnalyseurDTD/ -IAnalyseurXML/ -IXslt


all: analyseDTD analyseXML 
	g++ $(FLAGS) -o analyse $(SOURCES)
	
analyseDTD:
	make -C AnalyseurDTD lex

analyseXML:
	make -C AnalyseurXML lex

clean:
	make -C AnalyseurDTD clean
	make -C AnalyseurXML clean
	rm -f analyse Xslt/*.o Tests/*.htm* *.htm*

