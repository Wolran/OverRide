
#include <stdio.h>
#include <string.h>

int auth(char *s, int a2)
{
	int i;
	int v4;
	int v5;

	s[strcspn(s, "\n")] = 0;
	v5 = strnlen(s, 32);
	if ( v5 <= 5 )
		return 1;
	v4 = (s[3] ^ 0x1337) + 6221293;
	for ( i = 0; i < v5; ++i )
	{
	  v4 += (v4 ^ (unsigned int)s[i]) % 0x539;
	}
	printf("%d\n",v4);
}

int main(int argc, const char **argv, const char **envp)
{
  	int v4;
  	char s[]= "Le_meilleur_CUB3D";
 	auth(s, v4);
  	return 0;
}