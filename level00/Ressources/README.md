# OverRide : [level00]

### Observation :
En arrivant sur le level00 on trouve un exécutable nommé level00.\
Quand nous essayons de le lancer cela nous demande un mot de passe. \
Regardons donc avec gdb ou un decompilateur.

---

#### Source décompilée:
```c
//----- (08048494) --------------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v4; // [esp+1Ch] [ebp-4h] BYREF

  puts("***********************************");
  puts("* \t     -Level00 -\t\t  *");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf("%d", &v4);
  if ( v4 == 5276 )
  {
    puts("\nAuthenticated!");
    system("/bin/sh");
    return 0;
  }
  else
  {
    puts("\nInvalid Password!");
    return 1;
  }
}
```

#### Détails du programme:
```bash
-rwsr-s---+ 1 level01 users   7280 Sep 10  2016 level00
```

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>` | Envois la valeur de notre stdin a l'intérieur de la variable `v4` et la compare à `5276`, si cette valeur est identique cela nous donne acces a un shell en temp qu'utilisateur level01.|



#### Conclusions:
Nous allons juste donner le bon mot de passe `5276` pour acceder au shell et pouvoir afficher le pass de level01.


----
Résolution:
----
Nous injectons notre nombre `5276` dans la variable `v4`.


#### Commande:
```bash
(echo 5276; echo $(echo 'cat /home/users/level01/.pass')) | ./level00
```

**Flag :** uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL