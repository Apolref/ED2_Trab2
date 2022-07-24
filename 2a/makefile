all : exercicio2a

run:
	./exercicio2a
	
clean:
	rm -f *.o
	rm -f exercicio2a
	
exercicio2a.o : exercicio2a.c
	gcc -o exercicio2a.o -c exercicio2a.c
	
exercicio2a : exercicio2a.o
	gcc -o exercicio2a exercicio2a.o
	
