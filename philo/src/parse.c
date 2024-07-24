/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:36:49 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/24 22:06:51 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * Converts a string to an integer.
 * 
 * @param str The string to convert.
 * @return The converted integer if successful, -1 otherwise.
 */
static int	get_number(char *str)
{
	long	num;

	if (!*str)
		return (-1);
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str++ - '0');
		if (num > INT_MAX)
			return (-1);
	}
	if (*str)
		return (-1);
	return (num);
}

/**
 * Initializes the settings structure with the provided parameters.
 *
 * @param s The settings structure to initialize.
 * @param param An array of strings containing the parameters.
 *              param[0] - Number of philosophers
 *              param[1] - Time to die (in milliseconds)
 *              param[2] - Time to eat (in milliseconds)
 *              param[3] - Time to sleep (in milliseconds)
 *              param[4] - Number of meals (optional)
 * @return 1 if the initialization is successful, 0 otherwise.
 */
int	settings_init(t_settings *s, char **param)
{
	s->num_of_philos = get_number(param[0]);
	s->time_to_die = get_number(param[1]);
	s->time_to_eat = get_number(param[2]);
	s->time_to_sleep = get_number(param[3]);
	s->num_of_meals = -2;
	if (param[4] != NULL)
		s->num_of_meals = get_number(param[4]);
	return (s->num_of_philos > 0
		&& s->num_of_philos <= 200
		&& s->time_to_die >= 60
		&& s->time_to_eat >= 60
		&& s->time_to_sleep >= 60
		&& s->num_of_meals != -1);
}
