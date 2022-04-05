/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:04:25 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/05 17:48:07 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/pipex_bonus.h"

// get_cmd
char	*get_cmd(t_stock bonus)
{
	char	*tmp;
	char	*command;
	int		i;

	if (ft_strnstr(bonus.cmd_argemment[0], "/",
			ft_strlen(bonus.cmd_argemment[0])))
		return (bonus.cmd_argemment[0]);
	i = -1;
	bonus.cmd_paths = ft_split(bonus.paths, ':');
	while (bonus.cmd_paths[++i])
	{
		tmp = ft_strjoin("/", bonus.cmd_argemment[0]);
		command = ft_strjoin(bonus.cmd_paths[i], tmp);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
	}
	return (0);
}

// child own
void	child_own(t_stock bonus, char *argv[], char **envp)
{
	bonus.pid1 = fork();
	if (bonus.pid1 < 0)
		return_error("error");
	if (bonus.pid1 == 0)
	{
	  bonus.cmd_argemment = ft_split(argv[2], ' ');
		bonus.cmd = get_cmd(bonus);
		if (!bonus.cmd)
		{
			cmd_not_found(bonus.cmd_argemment[0]);
			// child_free(bonus.cmd_argemment);
			exit (EXIT_FAILURE);
		}
		close(bonus.fdpipe[0]);
		dup2(bonus.fdpipe[1], 1);
		close(bonus.fdpipe[1]);
		dup2(bonus.infile, 0);
		close(bonus.infile);
		if (execve(bonus.cmd, bonus.cmd_argemment, envp) == -1)
			return_error(bonus.cmd);
	}
}

// child tow
void	child_tow(t_stock bonus, char *argv[], char **envp)
{
	bonus.pid2 = fork();
	if (bonus.pid2 < 0)
		return_error("error");
	if (bonus.pid2 == 0)
	{
	  bonus.cmd_argemment = ft_split(argv[3], ' ');
		bonus.cmd = get_cmd(bonus);
		if (!bonus.cmd)
		{
			cmd_not_found(bonus.cmd_argemment[0]);
			// child_free(bonus.cmd_argemment);
			exit (EXIT_FAILURE);
		}
		close(bonus.fdpipe[1]);
		close(bonus.fd1pipe[0]);
		dup2(bonus.fdpipe[0], 0);
		// dup2(bonus.fd, 1);
		dup2(bonus.fd1pipe[1], 1);
		if (execve(bonus.cmd, bonus.cmd_argemment, envp) == -1)
			return_error(bonus.cmd);
	}
}

// child tree
void	child_tree(t_stock bonus, char *argv[], char **envp)
{
	bonus.pid3 = fork();
	if (bonus.pid3 < 0)
		return_error("error");
	if (bonus.pid3 == 0)
	{
	  bonus.cmd_argemment = ft_split(argv[4], ' ');
		bonus.cmd = get_cmd(bonus);
		if (!bonus.cmd)
		{
			cmd_not_found(bonus.cmd_argemment[0]);
			// child_free(bonus.cmd_argemment);
			exit (EXIT_FAILURE);
		}		
		close(bonus.fd1pipe[1]);
		dup2(bonus.fd1pipe[0], 0);
		dup2(bonus.outfile, 1);
		if (execve(bonus.cmd, bonus.cmd_argemment, envp) == -1)
			return_error(bonus.cmd);
	}
}