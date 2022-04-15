/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:40:29 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/15 17:38:52 by rarahhal         ###   ########.fr       */
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
	return (NULL);
}

static void	duplicat(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	child(t_stock bonus, char *argv[], char **envp)
{
	bonus.pid = fork();
	if (bonus.pid < 0)
		return_error("error");
	if (bonus.pid == 0)
	{
		bonus.cmd_argemment = ft_split(argv[bonus.indx
				+ 2 + bonus.heredoc], ' ');
		bonus.cmd = get_cmd(bonus);
		if (!bonus.cmd)
		{
			cmd_not_found(bonus.cmd_argemment[0]);
			child_free(bonus.cmd_argemment);
			exit (EXIT_FAILURE);
		}
		if (bonus.indx == 0)
			duplicat(bonus.infile, bonus.pipefd[1]);
		else if (bonus.indx == bonus.cmd_nbr - 1)
			duplicat(bonus.pipefd[2 * bonus.indx - 2], bonus.outfile);
		else
			duplicat(bonus.pipefd[2 * bonus.indx - 2],
				bonus.pipefd[2 * bonus.indx + 1]);
		close_pipes(&bonus);
		if (execve(bonus.cmd, bonus.cmd_argemment, envp) == -1)
			return_error(bonus.cmd);
	}
}
