/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:58:00 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/01 08:03:06 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * @brief Destroys a philosopher struct.
 *
 * This function is responsible for destroying a philosopher struct by freeing
 * the memory allocated for it and destroying the associated mutexes.
 *
 * @param content A pointer to the philosopher struct to be destroyed.
 */
void	destroy_philo(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	destroy_mutex(&philo->lock);
	destroy_mutex(&philo->fork);
	free(philo);
}

/**
 * Checks if the simulation has ended.
 *
 * @param obj The object containing informations about the program.
 * @return True if the simulation has ended, false otherwise.
 */
bool	is_ended(t_object *obj)
{
	return (read_value(&obj->obj_lock, &obj->ended));
}

/**
 * Reads the value of a variable while ensuring thread safety using a mutex.
 *
 * @param mutex The mutex used to synchronize access to the variable.
 * @param var   A pointer to the variable whose value is to be read.
 * @return      The value of the variable.
 */
long	read_value(t_mutex *mutex, long *var)
{
	long	ret;

	pthread_mutex_lock(&mutex->mutex);
	ret = *((long *)var);
	pthread_mutex_unlock(&mutex->mutex);
	return (ret);
}

/**
 * Updates the value of a variable with thread-safe access using a mutex.
 *
 * @param mutex The mutex used for synchronization.
 * @param var   A pointer to the variable to be updated.
 * @param new_value The new value to be assigned to the variable.
 */
void	write_value(t_mutex *mutex, long *var, long new_value)
{
	pthread_mutex_lock(&mutex->mutex);
	if (new_value == 0)
		*var = *var + 1;
	else
		*var = new_value;
	pthread_mutex_unlock(&mutex->mutex);
}
