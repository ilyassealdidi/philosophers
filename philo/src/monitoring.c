/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:40:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/21 04:15:39 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	destroy_philo(void *content)
{
	t_philo		*philo;

	philo = (t_philo *)content;
	pthread_join(philo->thrd, NULL);
	// pthread_mutex_destroy(&philo->fork);
	// pthread_mutex_destroy(&philo->lock);
	// free(philo);
}

static void	exiter(t_object *obj)
{
	if (obj->settings.num_of_philos > 1)
		lst_iter(obj->philos, destroy_philo);
	lst_clear(obj->philos);
}

static int	is_dead(t_philo *philo)
{
	long	last_eating_time;
	t_object	*obj;

	obj = philo->_parent;
	last_eating_time = read_value(&philo->lock, &philo->last_eating_time);
	if (get_current_time() - last_eating_time >= obj->settings.time_to_die)
	{
		pthread_mutex_lock(&obj->print_lock);
		pthread_mutex_lock(&obj->obj_lock);
		printf(DIE, get_current_time() - obj->start_time, philo->id);
		obj->ended = true;
		pthread_mutex_unlock(&obj->obj_lock);
		pthread_mutex_unlock(&obj->print_lock);
		return (1);
	}
	return (0);
}

int	are_philos_full(t_object *obj)
{
	int	full_philos;

	full_philos = read_value(&obj->meals_lock, &obj->full_philos);
	if ((unsigned int)full_philos == obj->settings.num_of_philos)
		return (write_value(&obj->obj_lock, &obj->ended, true), 1);
	return (0);
}

void	monitoring(t_object *obj)
{
	t_list		*philos;

	sleeper(obj, obj->settings.time_to_die); //TO BE FIXED
	philos = obj->philos;
	while (1)
	{
		if (are_philos_full(obj) || is_dead(philos->content))
			return (exiter(obj));
		philos = philos->next;
	}
}
