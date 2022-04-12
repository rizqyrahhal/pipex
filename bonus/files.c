/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:32:40 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/11 21:31:28 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/bonus.h"

void    get_infile(char **argv, t_stock bonus)
{
    if (!ft_strncmp("here_doc", argv[1], 9))
        here_doc(argv[2], &bonus);
    else
    {
        bonus.infile = open(argv[1], O_RDONLY);
	    if (bonus.infile < 0)
		    return_error("infile error");
    }
}

void    get_outfile(char *argv, t_stock *bonus)
{
    if (bonus->heredoc)
        bonus->outfile = open(argv, O_CREAT | O_RDWR | O_APPEND, 0000644);
    else
        bonus->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
    if (bonus->outfile < 0)
		return_error("outfile error");
}