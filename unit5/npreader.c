#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char buf[128];
    int fd = open("mypipe", O_RDONLY);
    read(fd, buf, 128);
    printf("%s\n", buf);
    close(fd);
}

