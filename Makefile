#------------------------------------------------------------------------------
CPP=g++
SOURCE=lex.yy.c parser.tab.c src/ast.cc src/ast-eval.cc src/local-environment.cc src/ast-compile.cc src/icode.cc
MYPROGRAM=sclp
MYLIBRARY=$(CURDIR/utils)
LDFLAGS=-Wl,-rpath=$(CURDIR/utils)
CFLAGS=-std=c++0x
FLEX=flex
ALLHEADERS=utils/allheaders.h
BISON=bison
#-----------------------------------------------------------------------------

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)
	$(CPP) -include $(ALLHEADERS) -L$(MYLIBRARY) $(CFLAGS) $(LDFLAGS) $(SOURCE) -o $(MYPROGRAM) -lsclpshared -lfl -ly

lex.yy.c: src/scanner.l utils/parser.tab.h
	$(FLEX) -l --yylineno src/scanner.l
parser.tab.c parser.tab.h : src/parser.y
	$(BISON) -d  src/parser.y

clean:
	rm -f $(MYPROGRAM)
