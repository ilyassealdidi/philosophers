/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:12:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/15 12:35:12 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *param)
{
	t_object		*obj;
	t_philosopher	*philo;
	t_philosopher	*sib;

	philo = (t_philosopher *)((t_list *)param)->content;
	obj = philo->_parent;
	sib = (t_philosopher *)((t_list *)param)->next->content;
	while (philo->_parent->start_time == 0)
		;
	if (philo->id % 2 == 1)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		printf("Philo %d has taken a fork\n", philo->id);

		pthread_mutex_lock(&sib->fork);
		printf("Philo %d has taken a fork\n", philo->id);
		pthread_mutex_unlock(&sib->fork);
		pthread_mutex_unlock(&philo->fork);

		printf("Philo %d is eating\n", philo->id);
		usleep(obj->settings.time_to_eat);

		printf("Philo %d is sleeping\n", philo->id);
		usleep(obj->settings.time_to_sleep);
	}
	printf("End\n");
	return (NULL);
}
