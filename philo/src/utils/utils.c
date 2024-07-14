/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:58:00 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/15 00:24:11 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long	read_value(pthread_mutex_t *mutex, long *var)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *((long *)var);
	pthread_mutex_unlock(mutex);
	return (ret);
}

long   write_value(pthread_mutex_t *mutex, long *var, long new_value)
{
	long	*ptr;

	ptr = (long *)var;
	pthread_mutex_lock(mutex);
	if (new_value == 0)
		*ptr = *ptr + 1;
	else
		*ptr = new_value;
	pthread_mutex_unlock(mutex);
	return (*ptr);
}
