/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:12:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/21 11:39:08 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	*action(void *param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	while (philo->_parent->start_time == 0)
		;
	philo->last_eating_time = get_current_time();
	if (philo->id % 2 == 1)
	{
		print_action(philo, THINK);
		sleeper(50);
	}
	while (1)
	{
		if (eat(philo) == 0 || bedtime(philo) == 0 || think(philo) == 0)
			break ;
	}
	return (NULL);
}
