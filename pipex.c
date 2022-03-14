/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:42:14 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/14 18:39:48 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int main(int argc, char *argv[], char **envp)
{
    char *args[] = {"ls", "-la", NULL};
    // char *argss[] = {"grep", "fa", NULL};
    char *argss[] = {"ls", "-l", NULL};
    if (argc != 5)
    {
        write(1, "executed as follows: ./pipex file1 cmd1 cmd2 file2\n", 51);
        return (1);
    }
    // infile 
    int infile = open(argv[1], O_RDONLY);
    if (infile < 0)
    {
        perror("infile error");
        return (2);
    }
    // outfile
    int outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
    if (outfile < 0)
    {
        perror("infile error");
        return (3);
    }
    int     fd[2];
    pid_t   pid1;
    pid_t   pid2;
    
    if (pipe(fd) == -1)
    {
        perror("error in opining pipe");
        return (4);
    }
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("error");
        return (5);
    }
    // first child
    if (pid1 == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        dup2(infile, 0);
        close(infile);
        execve("/bin/ls", args, envp);
    }
    pid2 = fork();
    if (pid2 < 0)
    {
        perror("error");
        return (6);
    }
    // secend child
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        dup2(outfile, 1);
        close(outfile);
        execve("/bin/ls", argss, envp);
    }
    return (0);
}