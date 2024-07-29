# OverRide : [level06]

### Observation :
En arrivant sur le level06 on trouve un exécutable nommé level06.\
Quand nous essayons de le lancer cela nous demande un nom login puis un mot de passe. et le programme se ferme \
Regardons donc avec gdb ou un decompilateur.

---

#### Source décompilée:
```c
_BOOL4 __cdecl auth(char *s, int a2)
{
  int i; // [esp+14h] [ebp-14h]
  int v4; // [esp+18h] [ebp-10h]
  int v5; // [esp+1Ch] [ebp-Ch]

  s[strcspn(s, "\n")] = 0;
  v5 = strnlen(s, 32);
  if ( v5 <= 5 )
    return 1;
  if ( ptrace(PTRACE_TRACEME, 0, 1, 0) == -1 )
  {
    puts("\x1B[32m.---------------------------.");
    puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
    puts("\x1B[32m'---------------------------'");
    return 1;
  }
  else
  {
    v4 = (s[3] ^ 0x1337) + 6221293;
    for ( i = 0; i < v5; ++i )
    {
      if ( s[i] <= 31 )
        return 1;
      v4 += (v4 ^ (unsigned int)s[i]) % 0x539;
    }
    return a2 != v4;
  }
}
// 80485D0: using guessed type int __cdecl strnlen(_DWORD, _DWORD);

//----- (08048879) --------------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v4; // [esp+2Ch] [ebp-24h] BYREF
  char s[28]; // [esp+30h] [ebp-20h] BYREF
  unsigned int v6; // [esp+4Ch] [ebp-4h]

  v6 = __readgsdword(0x14u);
  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(s, 32, stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  __isoc99_scanf(&unk_8048A60, &v4);
  if ( auth(s, v4) )
    return 1;
  puts("Authenticated!");
  system("/bin/sh");
  return 0;
}
```

#### Détails du programme:
```bash
-rwsr-s---+ 1 level07 users   7907 Sep 10  2016 level06
```

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>` | Le main nous demande un nom d'utilisateur et le stock dans la variable `s`, puis un Serial qui est un mot de passe encrypter en fonction de votre login. Il va ensuite appeler la fonction `<auth>` avec votre nom d'utilisateur et le Serial.|
| `<auth>` | La fonction auth modifie notre login avec beaucoup d'opérations puis compare avec le Serial que l'on a donné.|


#### Conclusions:
Il faut trouver une solution pour avoir le même Serial que notre login après être passer dans la fonction `<auth>`.

----
Résolution:
----
Il y a 2 moyens d'obtenir le bon Serial:
- Comprendre tous les calculs qui sont faits dans la fonction auth et les faire en parallèle.
- Ou ... Bah changer la fonction auth de notre côté pour afficher directement le bon Serial...

On reprend juste le code du programme en enlevant toutes les sécurités:
```c

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
```
Avec le login: `"Le_meilleur_CUB3D"` (aller le voir, il est exceptionnel ♥), cela nous donne le Serial: `6240307`



#### Commande:
```bash
(echo "Le_meilleur_CUB3D"; echo "6240307"; echo $(echo 'cat /home/users/level07/.pass')) | ./level06
```

#### Flag: `GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8`
