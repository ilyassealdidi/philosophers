/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:40:40 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/14 04:39:31 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static t_philo	*create_philosopher(int id, t_object *parent)
{
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->id = id;
	philo->eaten_meals = 0;
	philo->_parent = parent;
	if (pthread_mutex_init(&philo->fork, NULL) != 0
		|| pthread_mutex_init(&philo->lock, NULL) != 0)
		return (free(philo), NULL);
	return (philo);
}

static int	threads_init(t_list *philos, int count)
{
	int			i;
	t_philo		*philo;

	i = -1;
	while (++i < count)
	{
		philo = (t_philo *)philos->content;
		if (pthread_create(&philo->thrd, NULL, action, philos) != 0)
			return (0);
		philos = philos->next;
	}
	return (1);
}

int	philos_init(t_object *obj)
{
	int			i;
	t_list		*node;
	t_philo		*philosopher;

	i = -1;
	while (++i < obj->settings.num_of_philos)
	{
		philosopher = create_philosopher(i + 1, obj);
		if (philosopher == NULL)
			return (lst_clear(obj->philos), 0);
		node = lst_new(philosopher);
		if (node == NULL)
			return (free(philosopher), lst_clear(obj->philos), 0);
		lst_addback(&obj->philos, node);
	}
	if (threads_init(obj->philos, obj->settings.num_of_philos) == 0)
		return (lst_clear(obj->philos), 0);
	if (write_value(&obj->obj_lock, &obj->start_time, get_current_time()) == 0)
		return (lst_clear(obj->philos), 0);
	return (1);
}
