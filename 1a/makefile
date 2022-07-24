all : exercicio1a

run:
	./exercicio1a
	
clean:
	rm -f *.o
	rm -f exercicio1a
	
exercicio1a.o : exercicio1a.c
	gcc -o exercicio1a.o -c exercicio1a.c
	
exercicio1a : exercicio1a.o
	gcc -o exercicio1a exercicio1a.o
	
	
