/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 04:11:08 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/01 08:24:17 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * Initializes a mutex.
 *
 * This function initializes a mutex using the pthread_mutex_init
 * function.
 * If the initialization is successful, the `is_initialized` flag of the `mutex`
 * variable is set to true.
 *
 * @param mutex A pointer to the mutex to be initialized.
 * @return 1 if the mutex is successfully initialized, 0 otherwise.
 */
int	create_mutex(t_mutex *mutex)
{
	if (pthread_mutex_init(&mutex->mutex, NULL) != 0)
		return (print_error(MUTEX_INIT_ERROR), 0);
	mutex->is_initialized = true;
	return (1);
}

/**
 * @brief Destroys a mutex.
 * 
 * This function destroys a mutex and sets its `is_initialized` flag to false.
 * If the mutex is not initialized, it does nothing.
 * 
 * @param mutex A pointer to the mutex to be destroyed.
 */
void	destroy_mutex(t_mutex *mutex)
{
	if (mutex->is_initialized)
		pthread_mutex_destroy(&mutex->mutex);
	mutex->is_initialized = false;
}

/**
 * Locks the specified mutex.
 *
 * @param mutex The mutex to lock.
 */
void	lock_mutex(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
}

/**
 * Unlocks a mutex.
 *
 * @param mutex The mutex to unlock.
 */
void	unlock_mutex(t_mutex *mutex)
{
	pthread_mutex_unlock(&mutex->mutex);
}
