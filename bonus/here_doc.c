/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:24:41 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/14 21:18:38 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/bonus.h"

void	here_doc(char *argv, t_stock *bonus)
{
	int		file;
	char	*line;

	file = open(".temporere", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return_error("ERR_HEREDOC");
	while (1)
	{
		write(1, "heredoc>", 9);
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
		return_error("ERR_HEREDOC");
	}
}
