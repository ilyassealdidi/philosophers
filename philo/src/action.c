/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:12:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/01 08:41:35 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * Prints the action performed by a philosopher along with the current time.
 *
 * @param philo   A pointer to the philosopher struct.
 * @param action  The action string to be printed.
 */
static void	print_action(t_philo *philo, char *action)
{
	t_object	*obj;
	long		time;

	obj = philo->_parent;
	lock_mutex(&obj->print_lock);
	time = get_current_time() - read_value(&obj->obj_lock, &obj->start_time);
	if (!is_ended(obj))
		printf(action, time, philo->id);
	unlock_mutex(&obj->print_lock);
}

/**
 * Function to perform the think action for a philosopher.
 * 
 * This function checks if the philosopher's parent process has ended. If it has,
 * the function returns 0. Otherwise, it prints the action of the philosopher as
 * "THINK" and returns 1.
 * 
 * @param philo A pointer to the philosopher structure.
 * @return 0 if the philosopher's parent process has ended, 1 otherwise.
 */
static int	think(t_philo *philo)
{
	if (is_ended(philo->_parent))
		return (0);
	print_action(philo, THINK);
	return (1);
}

/**
 * Function to perform the sleep action for a philosopher.
 * 
 * @param philo The philosopher to put to sleep.
 * @return Returns 0 if the philosopher has ended, 1 otherwise.
 */
static int	bedtime(t_philo *philo)
{
	t_object	*obj;

	obj = philo->_parent;
	if (is_ended(philo->_parent))
		return (0);
	print_action(philo, SLEEP);
	sleeper(philo->_parent, philo->_parent->settings.time_to_sleep);
	return (1);
}

/**
 * Function to perform the eat action for a philosopher.
 * 
 * @param node The node containing the philosopher.
 * @return Returns 0 if the philosopher has reached the maximum number of meals
 * or if the simulation has ended, otherwise returns 1.
 */
static int	eat(t_list *node)
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
	lock_mutex(&philo->fork);
	print_action(philo, TAKE_FORK);
	lock_mutex(&sib->fork);
	print_action(philo, TAKE_FORK);
	set_current_time(&philo->lock, &philo->last_eating_time);
	print_action(philo, EAT);
	sleeper(obj, obj->settings.time_to_eat);
	write_value(&philo->lock, &philo->eaten_meals, 0);
	unlock_mutex(&philo->fork);
	unlock_mutex(&sib->fork);
	return (1);
}

/**
 * Executes the actions of a philosopher.
 * 
 * @param param The parameter passed to the thread function.
 * @return void* Returns NULL when the thread function completes.
 */
void	*action(void *param)
{
	t_philo		*philo;
	t_object	*obj;
	long		start_time;

	philo = ((t_list *)param)->content;
	obj = philo->_parent;
	while (1)
	{
		start_time = read_value(&obj->obj_lock, &obj->start_time);
		if (start_time == -1)
			return (NULL);
		else if (start_time > 0)
			break ;
	}
	set_current_time(&philo->lock, &philo->last_eating_time);
	if (philo->id % 2 == 0)
		sleeper(obj, obj->settings.time_to_eat);
	while (eat(param) != 0 && bedtime(philo) != 0 && think(philo) != 0)
		;
	return (NULL);
}
