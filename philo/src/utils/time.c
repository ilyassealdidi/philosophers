/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:23:23 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/21 04:09:59 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long	set_current_time(pthread_mutex_t *lock, long *time)
{
	long	current_time;

	current_time = get_current_time();
	if (current_time == 0)
		return (0);
	return (write_value(lock, time, current_time), current_time);
}

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (print_error(GETTIMEOFDAY_ERROR), 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleeper(t_object *obj, long time)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time && !is_ended(obj))
		usleep(100);
}
