/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:19:47 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/15 16:29:59 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_free(t_stock *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_argemment[i])
		free(pipex->cmd_argemment[i++]);
	free(pipex->cmd_argemment);
}

char *get_cmd(t_stock pipex)
{
		char *command = ft_strjoin("/", pipex.cmd_argemment[0]);
		char *tmp;
		int	i;
		
		i = 0;
		pipex.cmd_paths = ft_split(pipex.paths, ':');
		while (pipex.cmd_paths)
		{
			tmp = ft_strjoin(pipex.cmd_paths[i], command);
			if(access(tmp, F_OK) == 0)
				return (tmp);
			i++;
		}
		return ("command not found!");
}

void	child_own(t_stock pipex, char *argv[], char **envp)
{
	pipex.pid1 = fork();
    if (pipex.pid1 < 0)
        return_error("error");
	if (pipex.pid1 == 0)
	{
		pipex.cmd_argemment = ft_split(argv[2], ' ');
		pipex.cmd = get_cmd(pipex);
		close(pipex.pipefd[0]);
		dup2(pipex.pipefd[1], 1);
		close(pipex.pipefd[1]);
		dup2(pipex.infile, 0);
		close(pipex.infile);
		if (execve(pipex.cmd, pipex.cmd_argemment, envp) == -1)
		{
			child_free(&pipex);
			return_error("error");
		}
	}
}

void	child_tow(t_stock pipex, char *argv[], char **envp)
{
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
    	return_error("error");
	if (pipex.pid2 == 0)
	{
		pipex.cmd_argemment = ft_split(argv[3], ' ');
		pipex.cmd = get_cmd(pipex);
		close(pipex.pipefd[1]);
		dup2(pipex.pipefd[0], 0);
		close(pipex.pipefd[0]);
		dup2(pipex.outfile, 1);
		close(pipex.outfile);
		if (execve(pipex.cmd, pipex.cmd_argemment, envp) == -1)
			child_free(&pipex);
		exit(1);
	}
}
