// gcc -o chal chal.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <asm/prctl.h>
#include <sys/prctl.h>

unsigned long long int *shared_buf;

void main() __attribute__ ((noreturn));

void init_proc()
{
  char buf[0x10];
  shared_buf = mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
  if (shared_buf > 0) {
    arch_prctl(0x1003, buf);
    printf("DEBUG: FS base %p\n", *(void**)buf);
    printf("DEBUG: shared buffer %p\n", shared_buf); 
    printf("DEBUG: printf %p\n", printf);
  }
  else {
    printf("error: Failed to initialze shared buffer");
    _exit(1);
  }
  setvbuf(stdin,NULL,_IONBF,0);
  setvbuf(stdout,NULL,_IONBF,0);
  setvbuf(stderr,NULL,_IONBF,0);
}

void vuln()
{
  unsigned long long int idx;
  unsigned long long int val;
  char local_buf[0x40];

  gets(local_buf);

  idx = *(unsigned long long int*)(local_buf + 0x00);
  val = *(unsigned long long int*)(local_buf + 0x08);
  shared_buf[idx] = val;

  idx = *(unsigned long long int*)(local_buf + 0x10);
  val = *(unsigned long long int*)(local_buf + 0x18);
  shared_buf[idx] = val;

  idx = *(unsigned long long int*)(local_buf + 0x20);
  val = *(unsigned long long int*)(local_buf + 0x28);
  shared_buf[idx] = val;

  idx = *(unsigned long long int*)(local_buf + 0x30);
  val = *(unsigned long long int*)(local_buf + 0x38);
  shared_buf[idx] = val;
}

void main()
{
  init_proc();
  vuln();
  _exit(0);
}
