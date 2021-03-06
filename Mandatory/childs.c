/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:19:47 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/19 22:55:41 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/pipex.h"

void	child_free(char **str, char *cmd)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	free(cmd);
}

char	*get_cmd(t_stock pipex)
{
	char	*tmp;
	char	*command;
	int		i;

	if (ft_strnstr(pipex.cmd_argemment[0], "/",
			ft_strlen(pipex.cmd_argemment[0])))
		return (pipex.cmd_argemment[0]);
	i = -1;
	while (pipex.cmd_paths[++i])
	{
		tmp = ft_strjoin("/", pipex.cmd_argemment[0]);
		command = ft_strjoin(pipex.cmd_paths[i], tmp);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
	}
	return (NULL);
}

void	child_own(t_stock pipex, char *argv[], char **envp)
{
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return_error("error");
	if (pipex.pid1 == 0)
	{
		pipex.infile = open(argv[1], O_RDONLY);
		if (pipex.infile < 0)
			return_error(argv[1]);
		pipex.cmd_argemment = ft_split(argv[2], ' ');
		pipex.cmd = get_cmd(pipex);
		if (!pipex.cmd)
		{
			cmd_not_found(pipex.cmd_argemment[0]);
			child_free(pipex.cmd_argemment, pipex.cmd);
			exit (EXIT_FAILURE);
		}
		close(pipex.pipefd[0]);
		dup2(pipex.pipefd[1], 1);
		close(pipex.pipefd[1]);
		dup2(pipex.infile, 0);
		close(pipex.infile);
		if (execve(pipex.cmd, pipex.cmd_argemment, envp) == -1)
			return_error(pipex.cmd);
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
		if (!pipex.cmd)
		{
			cmd_not_found(pipex.cmd_argemment[0]);
			child_free(pipex.cmd_argemment, pipex.cmd);
			exit (EXIT_FAILURE);
		}
		close(pipex.pipefd[1]);
		dup2(pipex.pipefd[0], 0);
		close(pipex.pipefd[0]);
		dup2(pipex.outfile, 1);
		close(pipex.outfile);
		if (execve(pipex.cmd, pipex.cmd_argemment, envp) == -1)
			return_error(pipex.cmd);
	}
}
