#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	if(n != 0) {
		goto A;
	}
	A: printf("%d", 1);
	return 0;
}

	
