#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

char *line = "testing named pipe";

int main() {
    int fd;
    mknod("mypipe", S_IFIFO | 0666, 0); 
    fd = open("mypipe", O_WRONLY);
    write(fd, line, strlen(line) + 1); // include the null terminator
    close(fd);
    return 0;
}

