#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    setreuid(geteuid(), geteuid());
    system("/home/hacker/very-secure-script");
    return 0;
}