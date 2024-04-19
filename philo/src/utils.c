/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:23:23 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/18 11:07:00 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_value(pthread_mutex_t *mtx, long *target)
{
	long	value;

	pthread_mutex_lock(mtx);
	value = *target;
	pthread_mutex_unlock(mtx);
	return (value);
}

void	set_value(pthread_mutex_t *mtx, long *target, long value)
{
	pthread_mutex_lock(mtx);
	*target = value;
	pthread_mutex_unlock(mtx);
}

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return (time.tv_sec * 1e6 + time.tv_usec);
}

void	sleeper(long time)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		;
}
