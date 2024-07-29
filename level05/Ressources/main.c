#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *s = getenv('f');
	printf("%p\n", (void *)s);
}