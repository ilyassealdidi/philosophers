/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:40:40 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/20 12:59:09 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_philosopher	*create_philosopher(int id, t_object *parent)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->eating_counter = 0;
	philo->_parent = parent;
	if (pthread_mutex_init(&philo->fork, NULL) != 0)
		return (NULL);
	return (philo);
}

static int	threads_init(t_list *philos, int count)
{
	int				i;
	t_philosopher	*philo;

	i = -1;
	while (++i < count)
	{
		philo = (t_philosopher *)philos->content;
		if (pthread_create(&philo->thrd, NULL, routine, philos->content) != 0)
			return (0);
		philos = philos->next;
	}
	return (1);
}

int	philos_init(t_object *obj)
{
	int				i;
	t_list			*item;
	t_philosopher	*philosopher;

	pthread_mutex_init(&obj->tools.end_locker, NULL);
	pthread_mutex_init(&obj->tools.die_locker, NULL);
	pthread_mutex_init(&obj->tools.eat_locker, NULL);
	i = -1;
	while (++i < obj->settings.num_of_philos)
	{
		philosopher = create_philosopher(i + 1, obj);
		if (!philosopher)
			return (lst_clear(obj->philos), 0);
		item = lst_new(philosopher);
		if (!item)
			return (free(philosopher), lst_clear(obj->philos), 0);
		lst_addback(&obj->philos, item);
	}
	if (threads_init(obj->philos, obj->settings.num_of_philos) == 0)
		return (lst_clear(obj->philos), 0);
	obj->start_time = get_current_time();
	if (obj->start_time == 0)
		return (lst_clear(obj->philos), 0);
	return (1);
}
