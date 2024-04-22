/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:20 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/22 10:25:04 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

static int	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (philo->eating_counter == philo->_parent->settings.num_of_meals)
		return (0);
	pthread_mutex_lock(fork);
	if (is_ended(philo->_parent))
		return (0);
	print_action(philo, TAKE_FORK);
	return (1);
}

int	eat(t_philo *philo)
{
	t_object	*obj;
	t_philo		*sib;

	obj = philo->_parent;
	sib = get_next_philo(philo);
	if (take_fork(philo, &philo->fork) == 0)
		return (0);
	if (take_fork(philo, &sib->fork) == 0)
		return (0);
	print_action(philo, EAT);
	pthread_mutex_lock(&obj->tools.die_locker);
	philo->last_eating_time = get_current_time();
	pthread_mutex_unlock(&obj->tools.die_locker);
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
