/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:40:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/15 00:35:00 by ialdidi          ###   ########.fr       */
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

void	monitoring(t_object *obj)
{
	t_list		*philos;
	t_philo		*philo;

	sleeper(obj, obj->settings.time_to_die / 2); //TO BE FIXED
	philos = obj->philos;
	while (1)
	{
		philo = philos->content;
		if (read_value(&obj->obj_lock, &obj->finished) == obj->settings.num_of_philos)
		{
			write_value(&obj->obj_lock, &obj->ended, true);
			exiter(obj);
			return ;
		}
		if ((get_current_time() - read_value(&philo->lock, &philo->last_eating_time)) >= obj->settings.time_to_die)
		{
			print_action(philo, DIE);
			write_value(&obj->obj_lock, &obj->ended, true);
			exiter(obj);
			return ;
		}
		philos = philos->next;
	}
}
