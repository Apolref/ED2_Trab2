all : exercicio2b

run:
	./exercicio2b
	
clean:
	rm -f *.o
	rm -f exercicio2b
	
exercicio2b.o : exercicio2b.c
	gcc -o exercicio2b.o -c exercicio2b.c
	
exercicio2b : exercicio2b.o
	gcc -o exercicio2b exercicio2b.o
	
