/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:36:49 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/13 01:15:52 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	get_number(char *str)
{
	long	num;

	if (!*str)
		return (-1);
	num = 0;
	while (*str >= '0' && *str <= '9')
		num = num * 10 + (*str++ - '0');
	if (*str)
		return (-1);
	if (num > INT_MAX || num < INT_MIN)
		return (-1);
	return (num);
}

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
