/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:12:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/19 11:18:46 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	print_action(t_object *obj, t_philosopher *philo, char *action)
{
	long	time;

	pthread_mutex_lock(&obj->tools.printing_mtx);
	// if ((get_current_time() - philo->last_meal_time) >= (obj->settings.time_to_die)
	// 	|| get_value(&obj->tools.mtx, (long *)&obj->is_ended) != 0)
	// 	return (end_action(obj), 0);
	time = (get_current_time() - obj->start_time) / 1000;
	printf("%ld %d %s\n", time, philo->id, action);
	if (*action != 'd')
		pthread_mutex_unlock(&obj->tools.printing_mtx);
	return (1);
}

void	end_action(t_object *obj)
{
	set_value(&obj->tools.mtx, (long *)&obj->is_ended, true);
}

static void	eat(t_object *obj, t_philosopher *philo, t_philosopher *sib)
{
	pthread_mutex_lock(&philo->fork);
	print_action(obj, philo, "has taken a fork");
	// if ((get_current_time() - philo->last_meal_time) >= obj->settings.time_to_die
	// 	|| get_value(&obj->tools.mtx, (long *)&obj->is_ended) != 0)
	// 	return (print_action(obj, philo, "died"), end_action(obj));
	pthread_mutex_lock(&sib->fork);
	print_action(obj, philo, "has taken a fork");
	print_action(obj, philo, "is eating");
	sleeper(obj->settings.time_to_eat);
	philo->eaten_meals++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&sib->fork);
	pthread_mutex_unlock(&philo->fork);
}

static void	bedtime(t_object *obj, t_philosopher *philo)
{
	print_action(obj, philo, "is sleeping");
	sleeper(obj->settings.time_to_sleep);
}

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
	philo->last_meal_time = get_current_time();
	if (philo->id % 2 == 1)
	{
		print_action(obj, philo, "is thinking");
		sleeper(100);
	}
	while (get_value(&obj->tools.mtx, (long *)&obj->is_ended) == 0)
	{
		if (philo->eaten_meals == obj->settings.num_of_meals)
			break ;
		eat(obj, philo, sib);

		bedtime(obj, philo);
		print_action(obj, philo, "is thinking");
	}
	return (end_action(obj), NULL);
}
