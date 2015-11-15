#include <stdio.h>
#include <stdlib.h>
int setup();

int setup(){
	FILE *f = fopen("CFILE.txt", "w+");
	fprintf(f, "Testing setup");
	close(f);

}
