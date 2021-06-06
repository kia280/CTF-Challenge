#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#define MAX_NUM 0x10

struct star
{
  long long int len_name;
  long long int x;
  long long int y;
  char *name;
};

unsigned int last_idx = 0;
struct star *list[MAX_NUM];

void init_proc()
{
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

void menu()
{
  puts("1) Record");
  puts("2) Delete");
  puts("3) Adjust");
  puts("4) Telescope");
  puts("5) Exit");
  printf("> ");
}

void read_str(char *buf, size_t len)
{
  int idx = 0;
  while(len--) {
    assert(read(0, buf + idx, 1) > 0);
    if (*(buf+idx) == '\n') {
      *(buf+idx) = 0;
      break;
    }
    idx++;
  }
}

int read_int()
{
  char buf[0x10];
  memset(buf, 0, 0x10);
  read_str(buf, 0x10 - 1);
  return atoi(buf);
}

long long int read_ll()
{
  char buf[0x10];
  memset(buf, 0, 0x10);
  read_str(buf, 0x10 - 1);
  return atoll(buf);
}

void record()
{
  struct star *new_star = (struct star*) malloc(sizeof(struct star));
  char *name_buf;
  if (last_idx < MAX_NUM) {
    puts("1. coordinate (x, y)");
    printf("x: ");
    new_star->x = read_ll();
    printf("y: ");
    new_star->y = read_ll();
    puts("2. name");
    printf("length: ");
    new_star->len_name = read_ll();
    name_buf = (char*) malloc(new_star->len_name);
    assert(name_buf != NULL);
    printf("name: ");
    read_str(name_buf, new_star->len_name);
    new_star->name = name_buf;
    list[last_idx++] = new_star;
  } else {
    puts("Not enough space");
    exit(1);
  }
}

void delete()
{
  unsigned int idx;
  puts("index: ");
  idx = read_int();
  if (idx < MAX_NUM && list[idx]) {
    list[idx]->len_name = 0;
    list[idx]->x = 0;
    list[idx]->y = 0;
    free(list[idx]->name);
    free(list[idx]);
  } else {
    puts("Invalid index");
    exit(1);
  }
}

void adjust()
{
  unsigned int idx;
  puts("index: ");
  idx = read_int();
  if (idx < MAX_NUM && list[idx]) {
    puts("coordinate (x, y)");
    printf("x: ");
    list[idx]->x = read_ll();
    printf("y: ");
    list[idx]->y = read_ll(); 
  } else {
    puts("Invalid index");
    exit(1);
  }
}

void telescope()
{
  unsigned int idx;
  puts("index: ");
  idx = read_int();
  if (idx < MAX_NUM && list[idx]) {
    printf("%s - (%lld, %lld)\n", list[idx]->name, list[idx]->x, list[idx]->y);
  } else {
    puts("Invalid index");
    exit(1);
  }
}

int main(int argc, char *argv[])
{
    init_proc();
    while (1) {
      menu();
      switch(read_int()) {
        case 1:
          record();
          break;
        case 2:
          delete();
          break;
        case 3:
          adjust();
          break;
        case 4:
          telescope();
          break;
        case 5:
          puts("Bye!");
          exit(0);
        default:
          puts("Invalid choice");
      }
    }
    return 0;
}
