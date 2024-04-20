/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:23:23 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/20 19:21:49 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// long	get_value(pthread_mutex_t *mtx, void *target)
// {
// 	long	value;

// 	pthread_mutex_lock(mtx);
// 	value = *target;
// 	pthread_mutex_unlock(mtx);
// 	return (value);
// }

void	set_value(pthread_mutex_t *mtx, long *target, long value)
{
	pthread_mutex_lock(mtx);
	*target = value;
	pthread_mutex_unlock(mtx);
}

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleeper(long time)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		;
}

t_philo	*get_next_philo(t_philo *philo)
{
	int				i;
	t_list			*philos;

	i = 1;
	philos = philo->_parent->philos;
	while (i < philo->_parent->settings.num_of_philos)
	{
		if (philo->id == ((t_philo *)(philos->content))->id)
			break ;
		philos = philos->next;
		i++;
	}
	return (philos->next->content);
}
