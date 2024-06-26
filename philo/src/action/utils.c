/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:35:08 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/15 08:20:54 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

bool	is_ended(t_object *obj)
{
	int		value;

	pthread_mutex_lock(&obj->tools.extra_locker);
	value = obj->ended;
	pthread_mutex_unlock(&obj->tools.extra_locker);
	return (value);
}

void	print_action(t_philo *philo, char *action)
{
	long	time;

	pthread_mutex_lock(&philo->_parent->tools.print_locker);
	time = get_current_time() - philo->_parent->start_time;
	printf(action, time, philo->id, action);
	if (action[14] != 'd')
		pthread_mutex_unlock(&philo->_parent->tools.print_locker);
}
