/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:24:41 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/10 16:19:54 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/bonus.h"

void    here_doc(char *argv, t_stock *bonus)
{
    int     file;
    // char*   line;

    file = open(".tmp_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
    if (file < 0)
        return_error("ERR_HEREDOC");
    while(1)
    {
        write(1, "heredoc>", 9);
        if (get_next_line(0, bonus->line) < 0)
            exit(1);
        if (!ft_strncmp(argv, bonus->line, ft_strlen(argv) + 1))
            break;
        write(file, bonus->line, ft_strlen(bonus->line));
        write(file, "\n", 1);
        free(bonus->line);
    }
    free(bonus->line);
    close(file);
    bonus->infile = open(".tmp_heredoc", O_RDONLY);
    if (bonus->infile < 0)
    {
        unlink(".tmp_heredoc");
        return_error("ERR_HEREDOC");
    }
    // (void)bonus;
    // (void)argv;
    // printf("%s\n%d\n", argv, bonus.heredoc);
}