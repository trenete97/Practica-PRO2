OPCIONS = -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: Autor.o Cita.o Cjt_autors.o Frase.o program.o Text.o
	g++ -o program.exe *.o $(OPCIONS)

Autor.o: Autor.cc 
	g++ -c Autor.cc $(OPCIONS)

Cita.o:	Cita.cc 
	g++ -c Cita.cc $(OPCIONS)

Cjt_autors.o: Cjt_autors.cc
	g++ -c Cjt_autors.cc $(OPCIONS)

Frase.o: Frase.cc 
	g++ -c Frase.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

Text.o:	Text.cc 
	g++ -c Text.cc $(OPCIONS)

practica.tar: *.cc 
	tar -cvf practica.tar *.cc *.hh Makefile

clean:
	rm *.o
	rm *.exe
