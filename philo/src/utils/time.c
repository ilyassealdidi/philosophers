/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:23:23 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/01 07:58:35 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * Sets the current time and returns it.
 *
 * @param lock The mutex lock to ensure thread safety when writing the value.
 * @param time A pointer to the variable where the current time will be stored.
 * @return The current time.
 */
long	set_current_time(t_mutex *lock, long *time)
{
	long	current_time;

	current_time = get_current_time();
	return (write_value(lock, time, current_time), current_time);
}

/**
 * Returns the current time in milliseconds.
 *
 * @return The current time in milliseconds.
 */
long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/**
 * Sleeps for a specified amount of time.
 *
 * @param obj The object containing informations about the program.
 * @param time The time to sleep in milliseconds.
 */
void	sleeper(t_object *obj, long time)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time && !is_ended(obj))
		usleep(100);
}
