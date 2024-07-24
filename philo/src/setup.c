/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:40:40 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/23 21:06:05 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * Creates the necessary mutexes for the main struct.
 * 
 * @param obj The main struct.
 * @return 0 if any of the mutexes failed to be created, 1 otherwise.
 */
static int	create_mutexes(t_object *obj)
{
	if (create_mutex(&obj->obj_lock) == 0
		|| create_mutex(&obj->print_lock) == 0
		|| create_mutex(&obj->meals_lock) == 0)
		return (0);
	return (1);
}

/**
 * @brief Destroys the mutexes used by the main struct.
 * 
 * This function destroys the mutexes used by the main struct, including
 * the object lock, print lock, and meals lock.
 * 
 * @param obj The main struct.
 */
static void	destroy_mutexes(t_object *obj)
{
	destroy_mutex(&obj->obj_lock);
	destroy_mutex(&obj->print_lock);
	destroy_mutex(&obj->meals_lock);
}

/**
 * Creates a new philosopher with the given ID and parent object.
 *
 * @param id The ID of the philosopher.
 * @param parent The main struct.
 * @return A pointer to the newly created philosopher,
 * or NULL if an error occurred.
 */
static t_philo	*create_philo(int id, t_object *parent)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (print_error(MALLOC_ERROR), NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->id = id;
	philo->_parent = parent;
	if (create_mutex(&philo->fork) == 0 || create_mutex(&philo->lock) == 0)
		return (destroy_philo(philo), print_error(MUTEX_INIT_ERROR), NULL);
	return (philo);
}

/**
 * Initializes threads for each philosopher.
 *
 * This function initializes threads for each philosopher in the given list.
 *
 * @param philos The list of philosophers.
 * @param count The number of philosophers.
 * @return Returns 1 if all threads were successfully initialized, 0 otherwise.
 */
static int	threads_init(t_list *philos, int count)
{
	t_philo	*philo;

	while (count--)
	{
		philo = (t_philo *)philos->content;
		if (create_thread(&philo->thread, action, philos) == 0)
			return (0);
		philos = philos->next;
	}
	return (1);
}

/**
 * Initializes the philosophers and their resources.
 * 
 * @param obj The object containing the settings and data for the philosophers.
 * @return 1 if initialization is successful, 0 otherwise.
 */
int	philos_init(t_object *obj)
{
	int		i;
	t_list	*node;
	t_philo	*philo;

	if (create_mutexes(obj) == 0)
		return (destroy_mutexes(obj), 0);
	i = 1;
	while (i <= obj->settings.num_of_philos)
	{
		philo = create_philo(i, obj);
		if (philo == NULL)
			return (lst_clear(obj->philos, destroy_philo), 0);
		node = lst_new(philo);
		if (node == NULL)
			return (free(philo), lst_clear(obj->philos, destroy_philo), 0);
		lst_addback(&obj->philos, node);
		i++;
	}
	if (threads_init(obj->philos, obj->settings.num_of_philos) == 0)
		return (write_value(&obj->obj_lock, &obj->start_time, -1),
			lst_clear(obj->philos, destroy_philo), 0);
	set_current_time(&obj->obj_lock, &obj->start_time);
	return (1);
}
