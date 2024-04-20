/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:35:08 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/20 15:14:23 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

bool	is_dead(t_philosopher *philo)
{
	size_t	time;

	time = get_current_time();
	return ((get_current_time() - philo->last_eating_time)
		>= (philo->_parent->settings.time_to_die));
}

bool	is_ended(t_object *obj)
{
	int		value;

	pthread_mutex_lock(&obj->tools.end_locker);
	value = obj->ended;
	pthread_mutex_unlock(&obj->tools.end_locker);
	return (value);
}

void	print_action(t_philosopher *philo, char *action)
{
	size_t	time;

	time = get_current_time() - philo->_parent->start_time;
	printf("%ld %d %s\n", time, philo->id, action);
	return ;
}
