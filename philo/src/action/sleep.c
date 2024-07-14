/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:32 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/14 05:24:56 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	bedtime(t_philo *philo)
{
	t_object	*obj;

	obj = philo->_parent;
	if (read_value(&obj->obj_lock, &obj->ended) == 1)
		return (0);
	print_action(philo, SLEEP);
	sleeper(obj, philo->_parent->settings.time_to_sleep);
	return (1);
}
