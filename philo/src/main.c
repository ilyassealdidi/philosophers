/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:21:01 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/10 00:11:25 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*alfalasifa(void *param)
{
	return (NULL);
}

t_philosopher	*philos_init(t_object *obj)
{
	int				i;
	t_philosopher	*philos;

	philos = (t_philosopher *)malloc(sizeof(t_philosopher) * obj->settings.num_of_philos);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < obj->settings.num_of_philos)
	{
		if (pthread_create(&philos[i].thrd, NULL, alfalasifa, obj) != 0
			|| pthread_mutex_init(&philos->fork, NULL) != 0)
			return (free(philos), NULL);
		philos[i].id = i + 1;
		philos[i].full = false;
		philos[i].eaten_meals = 0;
	}
	return (philos);
}

int	settings_init(t_settings *settings, char **param)
{
	settings->num_of_philos = get_number(param[0]);
	settings->time_to_die = get_number(param[1]);z`z`
	settings->time_to_eat = get_number(param[2]);
	settings->time_to_sleep = get_number(param[3]);
	settings->num_of_meals = get_number(param[4]); //FIXME: Ask if the number of meals could be zero
	return (settings->num_of_philos > 0
		&& settings->num_of_philos <= 200
		&& settings->time_to_die >= 60
		&& settings->time_to_eat >= 60
		&& settings->time_to_sleep >= 60
		&& settings->num_of_meals != 0);
}

int	main(int ac, char *av[])
{
	t_object	obj;

	if (ac < 5 || ac > 6)
		return (printf(FORMAT_ERROR), EXIT_FAILURE);
	if (!settings_init(&obj.settings, av + 1))
		return (printf("Invalid Input\n"), EXIT_FAILURE);
	// obj.philos = philos_init(obj.settings.num_of_philos); 
	while (1);
}
