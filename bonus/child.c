/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:40:29 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/18 21:31:24 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/bonus.h"

void	child_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	*get_cmd(t_stock *bonus)
{
	char	*tmp;
	char	*command;
	int		i;

	if (ft_strnstr(bonus->cmd_argemment[0], "/",
			ft_strlen(bonus->cmd_argemment[0])))
		return (bonus->cmd_argemment[0]);
	i = 0;
	bonus->cmd_paths = ft_split(bonus->env_path, ':');
	while(*bonus->cmd_paths)
	{
		tmp = ft_strjoin("/", bonus->cmd_argemment[0]);
		command = ft_strjoin(bonus->cmd_paths[i], tmp);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		bonus->cmd_paths++;
		i++;
	}
	return (NULL);
}

// static void	duplicat(int zero, int first)
// {
// 	dup2(zero, 0);
// 	dup2(first, 1);
// }

void	child(t_stock bonus, char *argv[], char **envp)
{
	int fd[2];

	if(pipe(fd) < 0)
		exit (1);
	bonus.pid = fork();
	if (bonus.pid < 0)
		return_error("error");
	if (bonus.pid == 0)
	{
		bonus.cmd_argemment = ft_split(argv[bonus.indx
				+ 2 + bonus.heredoc], ' ');
		bonus.cmd = get_cmd(&bonus);
		if (!bonus.cmd)
		{
			cmd_not_found(bonus.cmd_argemment[0]);
			child_free(bonus.cmd_argemment);
			exit (EXIT_FAILURE);
		}
		// if (bonus.indx == 0)
		// 	dup2(fd[1], 1);
		if (bonus.indx == bonus.cmd_nbr - 1)
			dup2(bonus.outfile, 1);
			// dup2(fd[0], 0);
			//duplicat(bonus.pipefd[2 * bonus.indx - 2], bonus.outfile);
		else if (bonus.indx < bonus.cmd_nbr - 1)
		{
			// dup2(fd[0], 0);
			dup2(fd[1], 1);
			//duplicat(bonus.pipefd[2 * bonus.indx - 2],
			//	bonus.pipefd[2 * bonus.indx + 1]);
		}
		// close_pipes(&bonus);
		close(fd[1]);
		close(fd[0]);
		if (execve(bonus.cmd, bonus.cmd_argemment, envp) == -1)
			return_error(bonus.cmd);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}
