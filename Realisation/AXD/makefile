# Macro definitions

# Executables
ECHO = @echo
CC = g++
RM = rm -rf

# Flags
DEBUG = -g
CFLAGS = -Wall -ansi -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# Files
EXE = axd
SOURCE = main.cpp
OBJ = main.o

# Other
ECH_DONE = $(ECHO) "--- done ---"

all: $(EXE) tools

axd: $(OBJ)
	$(ECHO) "--- linking exe ---"
	$(CC) $(LFLAGS) $(OBJ) -o $(EXE)
	$(ECH_DONE)

tools:
	$(ECHO) "--- building analysis tools ---"
	make -C ../AnalyseurXML
	make -C ../AnalyseurDTD
	$(ECH_DONE)

%.o: %.cpp
	$(ECHO) "--- compiling *.cpp ---"
	$(CC) $(CFLAGS) $< -o $@
	$(ECH_DONE)

clean:
	$(ECHO) "--- cleaning the mess ---"
	$(RM) *.o $(EXE)
	$(ECH_DONE)

cleanall: clean
	$(ECHO) "--- cleaning the mess and the tools' mess ---"
	make -C ../AnalyseurXML clean
	make -C ../AnalyseurDTD clean
	$(ECH_DONE)
