/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:20 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/15 00:13:12 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	t_object	*obj;

	obj = philo->_parent;
	pthread_mutex_lock(fork);
	if (read_value(&obj->obj_lock, &obj->ended) == 1)
		return (0);
	print_action(philo, TAKE_FORK);
	return (1);
}

static void release_forks(t_philo *philo, t_philo *sib)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&sib->fork);
}

int	eat(t_list *node)
{
	t_object	*obj;
	t_philo		*philo;
	t_philo		*sib;

	philo = node->content;
	sib = node->next->content;
	obj = philo->_parent;
	if (!take_fork(philo, &philo->fork) || !take_fork(philo, &sib->fork))
		return (0);
	print_action(philo, EAT);
	write_value(&philo->lock, &philo->last_eating_time, get_current_time());
	sleeper(obj, obj->settings.time_to_eat);
	philo->eaten_meals++;
	release_forks(philo, sib);

	return (1);
}
