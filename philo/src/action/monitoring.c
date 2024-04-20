/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:23:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/20 18:25:03 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	monitoring(t_object *obj)
{
	t_list			*philos;
	t_philosopher	*philo;

	while (obj->start_time == 0)
		;
	sleeper(50);
	philos = obj->philos;
	while (1)
	{
		philo = philos->content;
		pthread_mutex_lock(&obj->tools.eat_locker);
		if (philo->_parent->finished == philo->_parent->settings.num_of_philos)
		{
			obj->ended = true;
			return ;
		}
		pthread_mutex_unlock(&obj->tools.eat_locker);
		pthread_mutex_lock(&obj->tools.die_locker);
		if ((get_current_time() - philo->last_eating_time)
			>= (obj->settings.time_to_die))
		{
			obj->ended = true;
			print_action(philo, "dead");
			return ;
		}
		pthread_mutex_unlock(&obj->tools.die_locker);
		philos = philos->next;
	}
}
