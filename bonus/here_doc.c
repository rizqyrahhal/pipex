/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:24:41 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/15 15:50:24 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/bonus.h"

int	chek_hedredoc(char *argv, t_stock *bonus)
{
	if (argv && !ft_strncmp("here_doc", argv, 9))
	{
		bonus->heredoc = 1;
		return (6);
	}
	else
	{
		bonus->heredoc = 0;
		return (5);
	}
}

void	here_doc(char *argv, t_stock *bonus)
{
	int		file;
	char	*line;

	file = open(".temporere", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return_error("ERR_HEREDOC");
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (!ft_strncmp(argv, line, ft_strlen(argv) + 1))
			break ;
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		free(line);
	}
	free(line);
	close(file);
	bonus->infile = open(".temporere", O_RDONLY);
	if (bonus->infile < 0)
	{
		unlink(".temporere");
		return_error("ERR_heredoc_infile");
	}
}
