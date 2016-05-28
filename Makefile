all: run

run:  lcs.out 
	


lcs.out: lcs.c		
		gcc -o lcs.out lcs.c

	
clean: lcs.c 
	rm lcs.out
