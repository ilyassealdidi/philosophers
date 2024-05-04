/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:40:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/04 10:15:58 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	join_thread(void *content)
{
	pthread_join(((t_philo *)content)->thrd, NULL);
}

static void	exiter(t_object *obj)
{
	if (obj->settings.num_of_philos > 1)
		lst_iter(obj->philos, join_thread);
	lst_clear(obj->philos);
}

void	monitoring(t_object *obj)
{
	t_list		*philos;
	t_philo		*philo;

	while (obj->start_time == 0)
		;
	sleeper(obj->settings.time_to_die / 2);
	philos = obj->philos;
	while (1)
	{
		philo = philos->content;
		pthread_mutex_lock(&obj->tools.obj_locker);
		if (philo->_parent->finished == philo->_parent->settings.num_of_philos)
			return (obj->ended = true, exiter(obj));
		pthread_mutex_unlock(&obj->tools.obj_locker);
		pthread_mutex_lock(&obj->tools.philo_locker);
		if ((get_current_time() - philo->last_eating_time)
			>= obj->settings.time_to_die)
			return (obj->ended = true, print_action(philo, DIE), exiter(obj));
		pthread_mutex_unlock(&obj->tools.philo_locker);
		philos = philos->next;
	}
}
