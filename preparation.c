#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[], char **envp)
{
    /* #### execve() ####*/

    // char cmd[] = "/bin/ls";
    // char *argVec[] = {"ls", "-l", "-a", NULL};
    // char *envVec[] = {NULL};

    // printf("Start of execve call %s:\n", cmd);
    // printf("===================================================================\n");
    // if (execve(cmd, argVec, envVec) == -1)
    //     perror("Could not execute execve");
    // printf("Oops, something went wrong!\n");

    /* #### dup2() ####*/

    // int file = open("stdin.txt", O_WRONLY | O_CREAT, 0777);

    // dup2(file, 1);
    // printf("test");

    /* #### pipe() ####*/
    
    // int ary[] = {1, 2, 3, 6, 8, 8, 7, 9, 3};
    // int arySize = sizeof(ary) / sizeof(int);
    // int start, end;
    // int fd[2];
    // if  (pipe(fd) == -1)
    //     return (1);
    // int id = fork();
    // if (id == -1)
    //     return (2);
    // if (id == 0)
    // {
    //     start = 0;
    //     end = arySize / 2;
    // }
    // else
    // {
    //     wait(NULL);
    //     start = arySize / 2;
    //     end = arySize;
    // }
    // int sum = 0;
    // int i = start;
    // while (i < end)
    // {
    //     sum += ary[i];
    //     i++;
    // }
    // printf("Calculated partial sum: %d\n", sum);

    // if (id == 0)
    // {
    //     close(fd[0]);
    //     if (write(fd[1], &sum, sizeof(sum)) == -1)
    //         return (3);
    //     close(fd[1]);
    // }
    // else
    // {
    //     int sumFromChild;
    //     close(fd[1]);
    //     if (read(fd[0], &sumFromChild, sizeof(sumFromChild)) == -1)
    //         return (4);
    //     close(fd[0]);

    //     int totalSum = sum + sumFromChild;
    //     printf("Total sum is %d\n", totalSum);
    //     wait(NULL);
    // }

    /* #### pipe()*/ 
    /*[Communicating between process (using pipes) ####*/

    // int fd[2];
    // pid_t pid;
    // int input;
    // int output;
    // // fd[0]----> read
    // // fd[1]----> write
    // if (pipe(fd) == -1)
    // {
    //     printf("An errror ocurred with opening the pipe\n");
    //     return (1);
    // }
    // pid = fork();
    // if (pid == -1)
    // {
    //     perror("fork");
    //     return (2);
    // }
    // if (pid == 0)
    // {
    //     close(fd[0]);
    //     printf("Input a number : ");
    //     scanf("%d", &input);
    //     if (write(fd[1], &input, sizeof(int)) == -1)
    //     {
    //         printf("An error ocured with writing to eht pipe\n");
    //         return (3);
    //     }
    //     close(fd[1]);
    // }
    // else
    // {
    //     close(fd[1]);
    //     if (read(fd[0], &output, sizeof(int)) == -1)
    //     {
    //         printf("An error ocured with reading from the pipe\n");
    //         return (4);
    //     }
    //     close(fd[0]);
    //     printf("Got from child process %d\n", output);
    // }

    /* #### wait() ####*/
    
    // pid_t pid;
    // int status;
    // int x = 5;
    // int y = 10;
    // int z = x + y;
    // if (fork() == 0)
    // {
    //     printf("I' am the child, My pid is : %d\n", (int)getpid());
    //     return (z);
    // }
    // else
    // {
    //     pid = wait(&status);
    //     printf("z = %d\n", z);
    // }
    // printf("Parent pid = %d, return status : %d\n", getpid(), WEXITSTATUS(status));
    // printf("Child pid = %d\n", pid);
    
    /* #### fork() #### */
    
    // pid_t pid;

    // for(int i = 0; i < 3; i++)
    // {
    //     pid = fork();
    // }
    // printf("I' am the process with pid %d\n", (int)getpid());
    return 0;
}