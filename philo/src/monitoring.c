/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:40:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/16 17:53:11 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * @brief Function to quit a thread.
 *
 * This function is responsible for quitting a thread by joining it.
 *
 * @param content A pointer to the thread content.
 */
static void	quit_thread(void *content)
{
	t_philo		*philo;

	philo = (t_philo *)content;
	join_thread(&philo->thread);
}

/**
 * Cleans up the resources of the threads and frees the allocation list for 
 * philos.
 *
 * @param obj The object to clean up.
 */
static void	clean_up(t_object *obj)
{
	if (obj->settings.num_of_philos > 1)
		lst_iter(obj->philos, quit_thread);
	else
	{
		unlock_mutex(&((t_philo *)obj->philos->content)->fork);
		detach_thread(&((t_philo *)obj->philos->content)->thread);
	}
	lst_clear(obj->philos, destroy_philo);
}

/**
 * Checks if a philosopher is dead. And prints a death message and updates
 * the object's ended flag
 * if the philosopher is dead.
 *
 * @param philo The philosopher to check.
 * @return 1 if the philosopher is dead, 0 otherwise.
 */
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

/**
 * Checks if all philosophers have eaten the required number of meals.
 *
 * @param obj The object containing informations about the program.
 * @return 1 if all philosophers have eaten the required number of meals,
 * 0 otherwise.
 */
static int	are_philos_full(t_object *obj)
{
	t_list		*philos;
	t_philo		*philo;
	int			i;

	if (obj->settings.num_of_meals == -2)
		return (0);
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

/**
 * Monitors the state of the philosophers.
 * 
 * @param obj The object containing informations about the program.
 */
void	monitoring(t_object *obj)
{
	t_list		*philos;

	sleeper(obj, obj->settings.time_to_die / 2);
	philos = obj->philos;
	while (1)
	{
		if (are_philos_full(obj) || is_dead(philos->content))
			return (clean_up(obj));
		philos = philos->next;
	}
}
