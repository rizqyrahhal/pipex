/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:37:28 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/19 14:52:49 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/pipex_bonus.h"

void	return_error(char *world)
{
	perror(world);
	exit (EXIT_FAILURE);
}

void	use_this(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit (EXIT_FAILURE);
}