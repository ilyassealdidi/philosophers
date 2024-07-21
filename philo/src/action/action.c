/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:12:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/21 00:48:33 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*action(void *param)
{
	t_philo		*philo;
	t_object	*obj;

	philo = ((t_list *)param)->content;
	obj = philo->_parent;
	while (read_value(&obj->obj_lock, &obj->start_time) == 0)
		;
	write_value(&philo->lock, &philo->last_eating_time, get_current_time());
	if (philo->id % 2 == 0)
		sleeper(obj, obj->settings.time_to_eat);
	while (1)
	{
		if (eat(param) == 0 || bedtime(philo) == 0 || think(philo) == 0)
			return (NULL);
	}
	return (NULL);
}
