/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:48:47 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/18 18:48:48 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int ft_numbers(int x)
{
    if (x < 0)
        x = -x;
    return (x);
}

int *ft_range(int start, int end)
{
    int *array;
    int i;
    int size;
    
    size = ft_numbers(end - start) + 1;
    array = malloc(size * sizeof(int) + 2);
    i = -1;
    if (end > start)
    {
        while (++i < size)
            array[i] = start + i;
    }
    else if (start > end)
    {
        while (++i < size)
            array[i] = start - i;
    }
    array[i + 1] = '\0';
    return(array);
}

int main()
{
   int *array;
    int i = -1;
    int start = 0;
    int end = 3;
    
    array = ft_range(start, end);
    while(++i < ft_numbers(end - start))
    {
        printf("%i, ", array[i]);
    }
    printf("%i, ", array[i]);
    
    return (0);
}