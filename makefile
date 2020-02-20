YFLAGS        = ‑d

PROGRAM       = mpint

CC            = gcc 

all:	$(PROGRAM)

y.tab.c y.tab.h: yacc.y
	yacc -d yacc.y

lex.yy.c: lex.l y.tab.h 
	flex lex.l

mpint:	lex.yy.c y.tab.c y.tab.h
	$(CC) -o mpint y.tab.c lex.yy.c -lfl

clean:
	rm mpint y.tab.c lex.yy.c y.tab.h
