/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:47:31 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/16 15:06:01 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    return_error(char *world)
{
    perror(world);
    exit (EXIT_FAILURE);
}

void    use_this(char *msg)
{
    write(2, msg, ft_strlen(msg));
    exit (EXIT_FAILURE);
}

void    cmd_not_nound(char *cmd)
{
    write(2, cmd, ft_strlen(cmd));
    write(2, ": command not found\n", 20);
    // exit (EXIT_FAILURE);
}