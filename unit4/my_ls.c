#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	printf("Running ls with system from within %s\n", argv[0]);
	system("ls -l");
	printf("Done.\n");
	exit(0);
}
