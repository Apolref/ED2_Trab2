all : exercicio2c

run:
	./exercicio2c
	
clean:
	rm -f *.o
	rm -f exercicio2c
	
exercicio2c.o : exercicio2c.c
	gcc -o exercicio2c.o -c exercicio2c.c
	
exercicio2c : exercicio2c.o
	gcc -o exercicio2c exercicio2c.o
	
