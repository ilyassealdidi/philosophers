/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:40:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/23 00:45:35 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	quit_thread(void *content)
{
	t_philo		*philo;

	philo = (t_philo *)content;
	join_thread(&philo->thread);
}

static void	exit_program(t_object *obj)
{
	if (obj->settings.num_of_philos > 1)
		lst_iter(obj->philos, quit_thread);
	else
		detach_thread(&((t_philo *)obj->philos->content)->thread);
	lst_clear(obj->philos, destroy_philo);
}

static int	is_dead(t_philo *philo)
{
	long		last_eating_time;
	t_object	*obj;

	obj = philo->_parent;
	last_eating_time = read_value(&philo->lock, &philo->last_eating_time);
	if (get_current_time() - last_eating_time >= obj->settings.time_to_die)
	{
		lock_mutex(&obj->print_lock);
		lock_mutex(&obj->obj_lock);
		printf(DIE, get_current_time() - obj->start_time, philo->id);
		obj->ended = true;
		unlock_mutex(&obj->obj_lock);
		unlock_mutex(&obj->print_lock);
		return (1);
	}
	return (0);
}

static int are_philos_full(t_object *obj)
{
	t_list		*philos;
	t_philo		*philo;
	int	i;

	i = 0;
	philos = obj->philos;
	while (i < obj->settings.num_of_philos)
	{
		philo = philos->content;
		if (read_value(&philo->lock, &philo->eaten_meals)
			!= obj->settings.num_of_meals)
			return (0);
		philos = philos->next;
		i++;
	}
	return (1);
}

void	monitoring(t_object *obj)
{
	t_list	*philos;

	sleeper(obj, obj->settings.time_to_die / 2);
	philos = obj->philos;
	while (1)
	{
		if (are_philos_full(obj) || is_dead(philos->content))
			return (exit_program(obj));
		philos = philos->next;
	}
}
