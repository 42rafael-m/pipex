#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    ssize_t size;
    char   buffer[5];
    int fd = open("prueba.txt", O_RDONLY);
    int fd2 = dup(fd);
    size = read(fd, buffer, 5);
    printf("buffer = %s\n", buffer);
    size = read(fd, buffer, 5);
    printf("buffer = %s\n", buffer);
    close(fd);
    size = read(fd2, buffer, 5);
    printf("buffer2 = %s\n", buffer);
    fd = open("prueba.txt", O_RDONLY);
    size = read(fd, buffer, 5);
    printf("buffer = %s\n", buffer);
    // printf("fd = %d\n", fd);
    // fd2 = dup(2);
    // printf("fd2 = %d\n", fd2);
    // size = read(fd, buffer, 4);
    // printf("buffer2 = %s\n", buffer);
    // close(fd2);
    // close(fd);
    // while (1);
    // char *argv[2];
    // char *envp[] = {
    // "PATH=/home/rms35/Documents/42/Cursus/pipex",
    // "HOME=/home/rms35",
    // NULL
    // };
    // argv[0] = "programa.c";
    // //argv[1] = "-l";
    // argv[1] = NULL;
    // execve("/home/rms35/Documents/42/Cursus/pipex/programa", argv, envp);
    // return (0);
}