/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:12:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/22 08:35:52 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*action(void *param)
{
	t_philo		*philo;
	t_object	*obj;
	long		start_time;

	philo = ((t_list *)param)->content;
	obj = philo->_parent;
	while (1)
	{
		start_time = read_value(&obj->obj_lock, &obj->start_time);
		if (start_time == -1)
			return (NULL);
		else if (start_time > 0)
			break ;
	}
	set_current_time(&philo->lock, &philo->last_eating_time);
	if (philo->id % 2 == 0)
		sleeper(obj, obj->settings.time_to_eat);
	while (eat(param) != 0 && bedtime(philo) != 0 && think(philo) != 0)
		;
	return (NULL);
}
