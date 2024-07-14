/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:12:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/15 00:13:18 by ialdidi          ###   ########.fr       */
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
		sleeper(obj, obj->settings.time_to_eat / 2);
	while (1)
	{
		if (eat(param) != 0 && bedtime(philo) != 0 && think(philo) != 0)
		{
			if (philo->eaten_meals == obj->settings.num_of_meals)
				return (write_value(&obj->obj_lock, &obj->finished, 0), NULL);
		}
		else
			break ;
		// if (eat(param) == 0 || bedtime(philo) == 0 || think(philo) == 0)
		// 	break ;
	}
	return (NULL);
}
