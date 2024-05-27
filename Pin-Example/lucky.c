#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	if( argc < 2 ) {
		printf("Usage: ./lucky [number]\n");
		return 0;
	}

	srand(time(0));
	int nLucky = rand() % 100;
	int nYourNum = atoi(argv[1]);
	if( nLucky == nYourNum ) {
		printf("You got the right number! (Lucky #: %d, Your #: %d)\n", 
			nLucky, nYourNum);
	} else {
		printf("Next time... (Lucky #: %d, Your #: %d)\n", 
			nLucky, nYourNum);
	}
	return 0;
}
