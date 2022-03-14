/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:44:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/14 19:54:18 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// open()
# include <fcntl.h>
// perror()
# include <stdio.h>
// write(), fork(), pipe(), close(), dup2(), execve()
# include <unistd.h>
// free(), malloc()
#include <stdlib.h>


char	**ft_split(char const *s, char c);


#endif