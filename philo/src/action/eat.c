/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:20 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/02 09:23:05 by ialdidi          ###   ########.fr       */
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

int	eat(t_list *node)
{
	t_object	*obj;
	t_philo		*philo;
	t_philo		*sib;

	philo = node->content;
	sib = node->next->content;
	obj = philo->_parent;
	if (!take_fork(philo, &philo->fork))
		return (0);
	if (!take_fork(philo, &sib->fork))
		return (0);
	print_action(philo, EAT);
	pthread_mutex_lock(&obj->tools.philo_locker);
	philo->last_eating_time = get_current_time();
	pthread_mutex_unlock(&obj->tools.philo_locker);
	sleeper(obj->settings.time_to_eat);
	philo->eating_counter++;
	pthread_mutex_lock(&philo->_parent->tools.obj_locker);
	if (philo->eating_counter == obj->settings.num_of_meals)
		obj->finished++;
	pthread_mutex_unlock(&philo->_parent->tools.obj_locker);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&sib->fork);
	return (1);
}
