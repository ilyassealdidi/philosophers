/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:20 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/22 09:30:41 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	take_forks(t_philo *philo, t_philo *sib)
{
	lock_mutex(&philo->fork);
	print_action(philo, TAKE_FORK);
	lock_mutex(&sib->fork);
	print_action(philo, TAKE_FORK);
}

static void	release_forks(t_philo *philo, t_philo *sib)
{
	unlock_mutex(&philo->fork);
	unlock_mutex(&sib->fork);
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
		return (0);
	if (is_ended(obj))
		return (0);
	take_forks(philo, sib);
	set_current_time(&philo->lock, &philo->last_eating_time);
	print_action(philo, EAT);
	sleeper(obj, obj->settings.time_to_eat);
	write_value(&philo->lock, &philo->eaten_meals, 0);
	release_forks(philo, sib);
	return (1);
}
