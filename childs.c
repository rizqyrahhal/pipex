/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:19:47 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/15 11:22:15 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void    free_split(t_stock pipex, char **cmd_argemment)
void    child_free(t_stock *pipex)
{
    int i;
    
    i = 0;
    while (pipex->cmd_argemment[i])
        free(pipex->cmd_argemment[i++]);
    free(pipex->cmd_argemment);
}

void    child_own(t_stock pipex, char *argv[],char **envp)
{
    pipex.cmd_argemment = ft_split(argv[2], ' ');
    
    close(pipex.pipefd[0]);
    dup2(pipex.pipefd[1], 1);
    close(pipex.pipefd[1]);
    dup2(pipex.infile, 0);
    close(pipex.infile);
    
    if (execve("/bin/ls", pipex.cmd_argemment, envp) == -1)
        child_free(&pipex);
        // child_free(pipex, pipex.cmd_argemment);
    exit(1);
}

void    child_tow(t_stock pipex, char *argv[], char **envp)
{
    pipex.cmd_argemment = ft_split(argv[3], ' ');

    close(pipex.pipefd[1]);
    dup2(pipex.pipefd[0], 0);
    close(pipex.pipefd[0]);
    dup2(pipex.outfile, 1);
    close(pipex.outfile);
    if (execve("/bin/ls", pipex.cmd_argemment, envp) == -1)
        child_free(&pipex);
        // child_free(pipex, pipex.cmd_argemment);
    exit(1);
}
