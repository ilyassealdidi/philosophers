/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:40:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/22 10:18:56 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	join_threads(t_object *obj)
{
	int		i;
	t_list	*node;
	t_philo	*philo;

	node = obj->philos;
	i = -1;
	while (++i < obj->settings.num_of_philos)
	{
		philo = node->content;
		pthread_join(philo->thrd, NULL);
		node = node->next;
	}
}

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
			return (obj->ended = true, join_threads(obj));
		pthread_mutex_unlock(&obj->tools.eat_locker);
		pthread_mutex_lock(&obj->tools.die_locker);
		if ((get_current_time() - philo->last_eating_time)
			>= obj->settings.time_to_die)
			return (obj->ended = true, join_threads(obj),
				print_action(philo, DIE));
		pthread_mutex_unlock(&obj->tools.die_locker);
		philos = philos->next;
	}
}
