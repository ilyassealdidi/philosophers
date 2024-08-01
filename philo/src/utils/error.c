/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:47:03 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/01 08:24:57 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * Calculates the length of a string.
 *
 * @param str The input string.
 * @return The length of the string.
 */
static int 	t_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * Prints an error message to the standard error stream.
 *
 * @param str The error message to be printed.
 */
void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}
