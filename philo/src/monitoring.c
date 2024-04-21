/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:40:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/21 12:05:57 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	monitoring(t_object *obj)
{
	t_list		*philos;
	t_philo		*philo;

	while (obj->start_time == 0)
		;
	sleeper(50);
	philos = obj->philos;
	while (1)
	{
		philo = philos->content;
		pthread_mutex_lock(&obj->tools.eat_locker);
		if (philo->_parent->finished == philo->_parent->settings.num_of_philos)
			return ((void)(obj->ended = true));
		pthread_mutex_unlock(&obj->tools.eat_locker);
		pthread_mutex_lock(&obj->tools.die_locker);
		if ((get_current_time() - philo->last_eating_time)
			>= obj->settings.time_to_die)
			return (obj->ended = true, print_action(philo, DIE));
		pthread_mutex_unlock(&obj->tools.die_locker);
		philos = philos->next;
	}
}