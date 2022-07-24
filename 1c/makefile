all : exercicio1c

run:
	./exercicio1c
	
clean:
	rm -f *.o
	rm -f exercicio1c
	
exercicio1c.o : exercicio1c.c
	gcc -o exercicio1c.o -c exercicio1c.c
	
exercicio1c : exercicio1c.o
	gcc -o exercicio1c exercicio1c.o
	
	
