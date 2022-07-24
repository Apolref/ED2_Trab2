all : exercicio1d

run:
	./exercicio1d
	
clean:
	rm -f *.o
	rm -f exercicio1d
	
exercicio1d.o : exercicio1d.c
	gcc -o exercicio1d.o -c exercicio1d.c
	
exercicio1d : exercicio1d.o
	gcc -o exercicio1d exercicio1d.o
	
	
