/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:42:14 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/15 11:21:16 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

void    close_pipes(t_stock *pipex)
{
    close(pipex->pipefd[0]);
    close(pipex->pipefd[1]);
}

int main(int argc, char *argv[], char **envp)
{
    t_stock pipex;
    // char *args[] = {"ls", "-la", NULL};
    //char **args = ft_split(argv[2], ' '); /// ajoute ou child_own
    char **argss = ft_split(argv[3], ' ');
    // char *argss[] = {"ls", "-l", NULL};
    if (argc != 5)
    {
        write(1, "executed as follows: ./pipex file1 cmd1 cmd2 file2\n", 51);
        return (1);
    }
    // infile 
    pipex.infile = open(argv[1], O_RDONLY);
    if (pipex.infile < 0)
    {
        perror("infile error");
        return (2);
    }
    // outfile
    pipex.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
    if (pipex.outfile < 0)
    {
        perror("infile error");
        return (3);
    }
    
    if (pipe(pipex.pipefd) == -1)
    {
        perror("error in opining pipe");
        return (4);
    }
    // pid_t pid1;
    pipex.pid1 = fork();
    if (pipex.pid1 < 0)
    {
        perror("error");
        return (5);
    }
    // first child
    if (pipex.pid1 == 0)
        child_own(pipex, argv, envp);
    pipex.pid2 = fork();
    if (pipex.pid2 < 0)
    {
        perror("error");
        return (6);
    }
    // secend child
    if (pipex.pid2 == 0)
        child_tow(pipex, argv, envp);
    close_pipes(&pipex);
    waitpid(pipex.pid1, NULL, 0);
    waitpid(pipex.pid2, NULL, 0);
    // child_free(pipex, pipex.cmd_argemment);
    // child_free(&pipex);
    
    return (0);
}