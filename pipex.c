/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:42:14 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/16 12:45:14 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

void checkLeaks(void)
{
	// system("leaks a.out");
	system("leaks pipex");
}

void    close_pipes(t_stock *pipex)
{
    close(pipex->pipefd[0]);
    close(pipex->pipefd[1]);
}

char    *find_path(char **envp)
{
    while (ft_strncmp("PATH", *envp, 4) != 0)
        envp++;
    return (*envp + 5);
}

int main(int argc, char *argv[], char **envp)
{
    t_stock pipex;
    
    if (argc != 5)
        use_this("executed as follows: ./pipex file1 cmd1 cmd2 file2\n");
    // infile 
    pipex.infile = open(argv[1], O_RDONLY);
    if (pipex.infile < 0)
        return_error("infile error");
    // outfile
    pipex.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
    if (pipex.outfile < 0)
        return_error("infile error");
    // open pipes
    if (pipe(pipex.pipefd) == -1)
        return_error("error in opining pipe");
    // paths
    pipex.paths = find_path(envp);
    // first child
    child_own(pipex, argv, envp);
    // secend child
    child_tow(pipex, argv, envp);
    close_pipes(&pipex);
    // waiting childs process
    waitpid(pipex.pid1, NULL, 0);
    waitpid(pipex.pid2, NULL, 0);
    // child_free(&pipex);
    
    atexit(checkLeaks);
    return (0);
}