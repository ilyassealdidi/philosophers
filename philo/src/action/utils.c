/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:35:08 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/21 04:11:27 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	print_action(t_philo *philo, char *action)
{
	t_object	*obj;
	long		time;

	obj = philo->_parent;
	pthread_mutex_lock(&obj->print_lock);
	time = get_current_time() - read_value(&obj->obj_lock, &obj->start_time);
	if (!is_ended(obj))
		printf(action, time, philo->id);
	pthread_mutex_unlock(&obj->print_lock);
}
