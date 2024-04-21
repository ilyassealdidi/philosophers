/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:35:08 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/21 12:01:23 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

bool	is_ended(t_object *obj)
{
	int		value;

	pthread_mutex_lock(&obj->tools.end_locker);
	value = obj->ended;
	pthread_mutex_unlock(&obj->tools.end_locker);
	return (value);
}

void	print_action(t_philo *philo, char *action)
{
	long	time;

	pthread_mutex_lock(&philo->_parent->tools.print_locker);
	time = get_current_time() - philo->_parent->start_time;
	printf(action, time, philo->id, action);
	if (*action != 'd')
		pthread_mutex_unlock(&philo->_parent->tools.print_locker);
	return ;
}

t_philo	*get_next_philo(t_philo *philo)
{
	int				i;
	t_list			*philos;

	i = 1;
	philos = philo->_parent->philos;
	while (i < philo->_parent->settings.num_of_philos)
	{
		if (philo->id == ((t_philo *)(philos->content))->id)
			break ;
		philos = philos->next;
		i++;
	}
	return (philos->next->content);
}
