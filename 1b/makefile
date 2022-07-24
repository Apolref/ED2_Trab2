all : exercicio1b

run:
	./exercicio1b
	
clean:
	rm -f *.o
	rm -f exercicio1b
	
exercicio1b.o : exercicio1b.c
	gcc -o exercicio1b.o -c exercicio1b.c
	
exercicio1b : exercicio1b.o
	gcc -o exercicio1b exercicio1b.o
	
	
