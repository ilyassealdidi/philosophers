/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:58:00 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/22 21:39:57 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	destroy_philo(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	destroy_mutex(&philo->lock);
	destroy_mutex(&philo->fork);
	free(philo);
}

bool	is_ended(t_object *obj)
{
	return (read_value(&obj->obj_lock, &obj->ended));
}

long	read_value(t_mutex *mutex, long *var)
{
	long	ret;

	pthread_mutex_lock(&mutex->mutex);
	ret = *((long *)var);
	pthread_mutex_unlock(&mutex->mutex);
	return (ret);
}

void	write_value(t_mutex *mutex, long *var, long new_value)
{
	pthread_mutex_lock(&mutex->mutex);
	if (new_value == 0)
		*var = *var + 1;
	else
		*var = new_value;
	pthread_mutex_unlock(&mutex->mutex);
}
