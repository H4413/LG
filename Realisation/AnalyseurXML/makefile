# Macro definitions

# Executables
ECHO = @echo
CC = g++
RM = rm -rf

# Flags
DEBUG = -g -DYYDEBUG=1
INCLUDE = -I../AnalyseurDTD/
CFLAGS = -Wall -ansi -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# Files
EXE = analyseXML
SOURCE = Xml.cpp \
	 lex.yy.c \
	 xml.tab.c
OBJ = Xml.o \
      lex.yy.o \
      xml.tab.o

# Other
ECH_DONE = $(ECHO) "### done"

# Rules Britannia

all: $(EXE)
	$(ECHO) "yomama"

analyseXML: $(OBJ)
	$(ECHO) "### linking exe"
	$(CC) $(LFLAGS) $(OBJ) -o $(EXE)
	$(ECH_DONE)

%.o: %.cpp %.c
	$(ECHO) "### Running Flex and Bison"
	flex  xml.l
	bison --debug --verbose --defines=yy.tab.h xml.y
	$(ECH_DONE)
	$(ECHO) "### Compiling *.cpp"
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDE)
	$(ECH_DONE)

clean:
	$(ECHO) "### cleaning the mess"
	$(RM) *.o $(EXE)
	$(RM) *.tab.c lex.*.c *.tab.h *.output
	$(ECH_DONE)
