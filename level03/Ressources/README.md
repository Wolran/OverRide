# OverRide : [level03]

### Observation :
En arrivant sur le level03 on trouve un exécutable nommé level03.\
Quand nous essayons de le lancer cela nous demande un mot de passe. \
Regardons donc avec gdb ou un decompilateur.

---

#### Source décompilée:
```c
int __cdecl decrypt(char a1)
{
  unsigned int i; // [esp+20h] [ebp-28h]
  unsigned int v3; // [esp+24h] [ebp-24h]
  char v4[29]; // [esp+2Bh] [ebp-1Dh] BYREF

  *(_DWORD *)&v4[17] = __readgsdword(0x14u);
  strcpy(v4, "Q}|u`sfg~sf{}|a3");
  v3 = strlen(v4);
  for ( i = 0; i < v3; ++i )
    v4[i] ^= a1;
  if ( !strcmp(v4, "Congratulations!") )
    return system("/bin/sh");
  else
    return puts("\nInvalid Password");
}
// 8048746: positive sp value 4 has been found

//----- (08048747) --------------------------------------------------------
int __cdecl test(int a1, int a2)
{
  int result; // eax
  char v3; // al

  switch ( a2 - a1 )
  {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
      result = decrypt(a2 - a1);
      break;
    default:
      v3 = rand();
      result = decrypt(v3);
      break;
  }
  return result;
}

//----- (0804885A) --------------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  unsigned int v3; // eax
  int savedregs; // [esp+20h] [ebp+0h] BYREF

  v3 = time(0);
  srand(v3);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf("%d", &savedregs);
  test(savedregs, 322424845);
  return 0;
}
```

#### Détails du programme:
```bash
-rwsr-s---+ 1 level04 users   7677 Sep 10  2016 level03
```

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>` | La fonction main fait un scanf de notre stdin et le place dans un int: `savedregs` puis appel la fonction `test` avec en parametre notre stdin et le nombre `322424845` |
| `<test>` | La fonction test vas soustraire notre nombre a `322424845` puis vas faire un switch case avec le résultat, si on arrive a rentrer dans la case 21 cela vas nous faire entrer dans la fonction decrypt sinon courage avec le random: `v3 = rand()`|
| `<decrypt>` | La fonction decrypt vas placer une chaine de caractere encrypter à l'interieur de `v4` puis vas `xor` `v4` avec notre nombre et compare le resultat de `v4` avec la chaine `"Congratulations!"` pour savoir si v4 a bien été decoder, cela nous donne acces à un shell, sinon cela nous affiche `"Invalid Password"`. |


#### Conclusions:
Nous allons devoir donner un nombre en entrée qui est entre `322424845-1 et 322424845-21` pour que l'operation de `test` nous envoie pas dans `decrypt` avec un nombre random. \
Nous allons devoir trouver quel est le bon nombre pour que l'operation `xor` arrive a decrypter `v4`.

----
Résolution:
----

Inverser l'operation xor sur chaque octets:

```shell
"Q}|u`sfg~sf{}|a3" = 01010001 01111101 01111100 01110101 01100000 01110011 01100110 01100111 01111110 01110011 01100110 01111011 01111101 01111100 01100001 00110011
						^	 
"Congratulations!" = 01000011 01101111 01101110 01100111 01110010 01100001 01110100 01110101 01101100 01100001 01110100 01101001 01101111 01101110 01110011 00100001
						=	
Résultat		   = 00010010 00010010 00010010 00010010 00010010 00010010 00010010 00010010 00010010 00010010 00010010 00010010 00010010 00010010 00010010 00010010
```
Cela nous donne `00010010` à chaque fois, donc `18` en décimal.

On devra donc donner `322424845 - 18 =  322424827` pour que test le transforme juste en `18` et que le xor fonctionne.

#### Commande:
```bash
(echo '322424827'; echo $(echo 'cat /home/users/level04/.pass')) | /home/users/level03/level03
```

**Flag :** kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
