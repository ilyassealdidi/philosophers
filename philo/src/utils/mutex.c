/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 04:11:08 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/23 00:14:27 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	create_mutex(t_mutex *mutex)
{
	if (pthread_mutex_init(&mutex->mutex, NULL) != 0)
		return (print_error(MUTEX_INIT_ERROR), 0);
	mutex->is_initialized = true;
	return (1);
}

void	destroy_mutex(t_mutex *mutex)
{
	if (mutex->is_initialized)
		pthread_mutex_destroy(&mutex->mutex);
	mutex->is_initialized = false;
}

void	lock_mutex(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
}

void	unlock_mutex(t_mutex *mutex)
{
	pthread_mutex_unlock(&mutex->mutex);
}
