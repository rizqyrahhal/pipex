/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:42:14 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/15 14:12:49 by rarahhal         ###   ########.fr       */
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
    
    if (argc != 5)
        error_msg("executed as follows: ./pipex file1 cmd1 cmd2 file2\n");
    // infile 
    pipex.infile = open(argv[1], O_RDONLY);
    if (pipex.infile < 0)
        return_error("infile error");
    // outfile
    pipex.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
    if (pipex.outfile < 0)
        return_error("infile error");
    if (pipe(pipex.pipefd) == -1)
        return_error("error in opining pipe");
    // t_pid
    pipex.pid1 = fork();
    if (pipex.pid1 < 0)
        return_error("error");
    // first child
    if (pipex.pid1 == 0)
        child_own(pipex, argv, envp);
    pipex.pid2 = fork();
    if (pipex.pid2 < 0)
    {
        return_error("error");
        return (6);
    }
    // secend child
    if (pipex.pid2 == 0)
        child_tow(pipex, argv, envp);
    close_pipes(&pipex);
    waitpid(pipex.pid1, NULL, 0);
    waitpid(pipex.pid2, NULL, 0);
    
    return (0);
}