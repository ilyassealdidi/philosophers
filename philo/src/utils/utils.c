/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:58:00 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/21 04:11:15 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

bool	is_ended(t_object *obj)
{
	return (read_value(&obj->obj_lock, &obj->ended));
}

long	read_value(pthread_mutex_t *mutex, long *var)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *((long *)var);
	pthread_mutex_unlock(mutex);
	return (ret);
}

void   write_value(pthread_mutex_t *mutex, long *var, long new_value)
{
	pthread_mutex_lock(mutex);
	if (new_value == 0)
		*var = *var + 1;
	else
		*var = new_value;
	pthread_mutex_unlock(mutex);
}
