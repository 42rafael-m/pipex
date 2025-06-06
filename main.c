// #include <unistd.h>
// #include <stdio.h>
// #include <sys/wait.h>
// #include <stdlib.h>
// #include <fcntl.h>

// int main()
// {
//      ssize_t bytes;
//     int status;
//     int n = 5;
//     int i = 0;
//     int pid;

//     while (i < n)
//     {
//         int pipefd[2];
//         pipe(pipefd);
//         pid = fork();
//         if (pid == 0)
//         {
//             // int j = 0;
//             // while (j < 20)
//             //     printf("j= %d, pid = %d\n", j++, getpid());

//             int infd = open("infile", O_RDONLY);
//             int fdout = open("outfile", O_WRONLY, 0644);
//             printf("%d\n", fdout);
//             char buffer;
           
//             bytes = 1;
//             printf("i = %d\n", i);
//             char c = i + 48;
//             if (i == 4)
//             {
//                 write(fdout, "EXIT\n", 5);
//                 exit(0);
//             }
//             while (bytes > 0)
//             {
//                 bytes = read(infd, &buffer, bytes);
//                 write(fdout, &buffer, 1);
//             }
//             close(fdout);
//             close(infd);
//             exit(0);
//         }
//         else
//         {
//             wait(&status);
//             i++;
//             printf("pid child = %d\n", pid);
//             //printf("waited for = %d\n", pid);
//         }
//     }
// }