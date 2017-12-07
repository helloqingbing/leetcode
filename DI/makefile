#Define some constants
IDIR  = include
CC = g++
CFLAGS = -I $(IDIR)

ODIR = obj
LDIR = lib
LIBS = -lm

SRC = src

# Add dependency here means if .h file changes ,we also need to rebuild the rule on 27
# g++ on mac cannot support .hxx well
_DEPS = Finder.h Movie.h Container.h Object.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = main.o Finder.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

# A rule: which means any file after ":" changed, it will rebuild this rule
# 	Will first build all *.cpp files, since they are in the dependency list
# -c : generate the object file
# -o $@ : put the output compilation in the file named on the left side of the :
# $< : the first item in the dependency list
# $@ : all context left side of :
# $^ : all context right side of :
$(ODIR)/%.o: $(SRC)/%.cpp $(DEPS)   
	$(CC) -c -o $@ $< $(CFLAGS)  

main : $(OBJ)
	$(CC) -g -o $@ $^ $(FLAGS) $(LIBS)

# if current dir contain clean file/folder, it always up-to-date.
# use this fake target can avoid this issue.
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm main

