#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    ssize_t size;
    char   *buffer;
    pid_t pid;
    pid_t pid2;
    int status;
    int pipefd[2];
    int fdin;
    int fdout;

    pid = 0;
    pid = 0;
    buffer = (char *)calloc(6, 1);
    
    pipe(pipefd);
    fdin = pipefd[0];
    fdout = pipefd[1];
    fdin = open("input", O_RDONLY);
    fdout = open("output", O_WRONLY);
    size = read(fdin, buffer, 5);
    pid = fork();
    if (pid)
        pid2 = waitpid(pid, &status, 0);
    if (!pid) 
    {
        write(2, buffer, 5);
        write(fdout, buffer, 5);
    }
    // printf("buffer = %s\n", buffer);
    printf("pid2 = %d\n", pid2);
    printf("pid = %d\n", pid);
    if (pid2 && pid2 != -1)
        _exit(status);
    free(buffer);
    close(pipefd[0]);
    // _exit(0);
    //_exit(0);
    // int fd2 = dup(fd);
    // size = read(fd, buffer, 5);
    // printf("buffer = %s\n", buffer);
    // close(fd);
    // size = read(fd2, buffer, 5);
    // printf("buffer2 = %s\n", buffer);
    // fd = open("prueba.txt", O_RDONLY);
    // size = read(fd, buffer, 5);
    // printf("buffer = %s\n", buffer);
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
    return (0);
}