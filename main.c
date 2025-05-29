#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    ssize_t size;
    char   buffer[4];
    int fd = open("prueba.txt", O_RDONLY);
    size = read(fd, buffer, 4);
    printf("%d\n", fd);
    while (1);
}