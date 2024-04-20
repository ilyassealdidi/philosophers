/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:12:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/20 18:18:52 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

static int	eat(t_philosopher *philo)
{
	t_object		*obj;
	t_philosopher	*sib;

	obj = philo->_parent;
	sib = get_next_philo(philo);
	pthread_mutex_lock(&philo->fork);
	if (is_ended(obj))
		return 0;
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&sib->fork);
	if (is_ended(obj))
		return 0;
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->_parent->tools.die_locker);
	philo->last_eating_time = get_current_time();
	pthread_mutex_unlock(&philo->_parent->tools.die_locker);
	pthread_mutex_lock(&philo->_parent->tools.eat_locker);
	philo->eating_counter++;
	if (philo->eating_counter == obj->settings.num_of_meals)
		obj->finished++;
	pthread_mutex_unlock(&philo->_parent->tools.eat_locker);
	sleeper(obj->settings.time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&sib->fork);
	return (1);
}

static int	bedtime(t_philosopher *philo)
{
	if (is_ended(philo->_parent) == true)
		return 0;
	print_action(philo, "is sleeping");
	sleeper(philo->_parent->settings.time_to_sleep);
	return (1);
}

static int	think(t_philosopher *philo)
{
	if (is_ended(philo->_parent) == true)
		return 0;
	print_action(philo, "is thinking");
	return (1);
}

void	*routine(void *param)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)param;
	while (philo->_parent->start_time == 0)
		;
	philo->last_eating_time = get_current_time();
	if (philo->id % 2 == 1)
	{
		print_action(philo, "is thinking");
		sleeper(50);
	}
	while (1)
	{
		if (eat(philo) == 0)
			break ;
		if (bedtime(philo) == 0)
			break ;
		if (think(philo) == 0)
			break ;
	}
	return (NULL);
}
