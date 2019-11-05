echo "Installing flex and bison:"
apt-get install flex bison
echo "Instaling pmj-interpreter:"
yacc -d yacc.y
lex lex.l
gcc y.tab.c lex.yy.c -lfl -o pmj-interpreter
rm y.tab.c
rm lex.yy.c
rm y.tab.h
mv pmj-interpreter /usr/bin/
echo "Interpreting welcome example:"
pmj-interpreter -f welcome.txt
