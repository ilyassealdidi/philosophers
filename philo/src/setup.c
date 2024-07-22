/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:40:40 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/23 00:38:23 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	create_mutexes(t_object *obj)
{
	if (create_mutex(&obj->obj_lock) == 0
		|| create_mutex(&obj->print_lock) == 0
		|| create_mutex(&obj->meals_lock) == 0)
		return (0);
	return (1);
}

static void	destroy_mutexes(t_object *obj)
{
	destroy_mutex(&obj->obj_lock);
	destroy_mutex(&obj->print_lock);
	destroy_mutex(&obj->meals_lock);
}

static t_philo	*create_philo(int id, t_object *parent)
{
	t_philo		*philo;

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

static int	threads_init(t_list *philos, int count)
{
	t_philo		*philo;

	while (count--)
	{
		philo = (t_philo *)philos->content;
		if (create_thread(&philo->thread, action, philos) == 0)
			return (0);
		philos = philos->next;
	}
	return (1);
}

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
