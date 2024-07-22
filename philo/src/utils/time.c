/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:23:23 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/22 21:47:47 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long	set_current_time(t_mutex *lock, long *time)
{
	long	current_time;

	current_time = get_current_time();
	return (write_value(lock, time, current_time), current_time);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleeper(t_object *obj, long time)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time && !is_ended(obj))
		usleep(100);
}
