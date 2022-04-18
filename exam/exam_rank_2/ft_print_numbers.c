/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:48:42 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/18 18:48:43 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_numbers(void)
{
    char diget;

    diget = '0';
    while (diget <= '9')
    {
        write(1, &diget, 1);
        diget++;
    }
}

int main()
{
    ft_print_numbers();
    return (0);
}
