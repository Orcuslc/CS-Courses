#include <stdio.h>
#include <malloc.h>

int *pi;
void foo() {
	pi = malloc(8*sizeof(int));
	free(pi);
}

void main() {
	pi = malloc(4*sizeof(int));
	foo();
}
