/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:12:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/15 08:20:54 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*action(void *param)
{
	t_philo		*philo;

	philo = ((t_list *)param)->content;
	while (philo->_parent->start_time == 0)
		;
	philo->last_eating_time = get_current_time();
	if (philo->id % 2 == 0)
		sleeper(philo->_parent->settings.time_to_eat / 2);
	while (1)
	{
		if (eat(param) == 0 || bedtime(philo) == 0 || think(philo) == 0)
			break ;
	}
	return (NULL);
}
