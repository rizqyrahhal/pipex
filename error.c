/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:47:31 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/15 13:59:49 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    return_error(char *world)
{
    perror(world);
    exit (0);
}

void    error_msg(char *msg)
{
    write(1, msg, ft_strlen(msg));
    exit (0);
}