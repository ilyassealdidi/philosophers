/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:20 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/21 04:12:25 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	take_forks(t_philo *philo, t_philo *sib)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, TAKE_FORK);
	pthread_mutex_lock(&sib->fork);
	print_action(philo, TAKE_FORK);
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
	if (philo->eaten_meals == obj->settings.num_of_meals)
		return (write_value(&obj->meals_lock, &obj->full_philos, 0), 0);
	if (is_ended(obj))
		return (0);
	take_forks(philo, sib);
	set_current_time(&philo->lock, &philo->last_eating_time);
	print_action(philo, EAT);
	sleeper(obj, obj->settings.time_to_eat);
	philo->eaten_meals++;
	release_forks(philo, sib);
	return (1);
}
